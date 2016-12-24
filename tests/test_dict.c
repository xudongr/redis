#include "dict.h"
#include "zmalloc.h"

#include <stdio.h>
#include <string.h>
#include <dict.h>


#define DICT_STATS_VECTLEN 50
static void _dictPrintStatsHt(dictht *ht) {
    unsigned long i, slots = 0, chainlen, maxchainlen = 0;
    unsigned long totchainlen = 0;
    unsigned long clvector[DICT_STATS_VECTLEN];

    if (ht->used == 0) {
        printf("No stats available for empty dictionaries\n");
        return;
    }

    for (i = 0; i < DICT_STATS_VECTLEN; i++) clvector[i] = 0;
    for (i = 0; i < ht->size; i++) {
        dictEntry *he;

        if (ht->table[i] == NULL) {
            clvector[0]++;
            continue;
        }
        slots++;
        /* For each hash entry on this slot... */
        chainlen = 0;
        he = ht->table[i];
        while(he) {
            chainlen++;
            he = he->next;
        }
        clvector[(chainlen < DICT_STATS_VECTLEN) ? chainlen : (DICT_STATS_VECTLEN-1)]++;
        if (chainlen > maxchainlen) maxchainlen = chainlen;
        totchainlen += chainlen;
    }
    printf("Hash table stats:\n");
    printf(" table size: %ld\n", ht->size);
    printf(" number of elements: %ld\n", ht->used);
    printf(" different slots: %ld\n", slots);
    printf(" max chain length: %ld\n", maxchainlen);
    printf(" avg chain length (counted): %.02f\n", (float)totchainlen/slots);
    printf(" avg chain length (computed): %.02f\n", (float)ht->used/slots);
    printf(" Chain length distribution:\n");
    for (i = 0; i < DICT_STATS_VECTLEN-1; i++) {
        if (clvector[i] == 0) continue;
        printf("   %s%ld: %ld (%.02f%%)\n",(i == DICT_STATS_VECTLEN-1)?">= ":"", i, clvector[i], ((float)clvector[i]/ht->size)*100);
    }
}

void dictPrintStats(dict *d) {
    _dictPrintStatsHt(&d->ht[0]);
    if (dictIsRehashing(d)) {
        printf("-- Rehashing into ht[1]:\n");
        _dictPrintStatsHt(&d->ht[1]);
    }
}

/* ----------------------- StringCopy Hash Table Type ------------------------*/

static unsigned int _dictStringCopyHTHashFunction(const void *key)
{
    return dictGenHashFunction(key, strlen(key));
}

static void *_dictStringDup(void *privdata, const void *key)
{
    int len = strlen(key);
    char *copy = zmalloc(len+1);
    DICT_NOTUSED(privdata);

    memcpy(copy, key, len);
    copy[len] = '\0';
    return copy;
}

static int _dictStringCopyHTKeyCompare(void *privdata, const void *key1,
                                       const void *key2)
{
    DICT_NOTUSED(privdata);

    return strcmp(key1, key2) == 0;
}

static void _dictStringDestructor(void *privdata, void *key)
{
    DICT_NOTUSED(privdata);

    zfree(key);
}

dictType dictTypeHeapStringCopyKey = {
        _dictStringCopyHTHashFunction, /* hash function */
        _dictStringDup,                /* key dup */
        NULL,                          /* val dup */
        _dictStringCopyHTKeyCompare,   /* key compare */
        _dictStringDestructor,         /* key destructor */
        NULL                           /* val destructor */
};

/* This is like StringCopy but does not auto-duplicate the key.
 * It's used for intepreter's shared strings. */
dictType dictTypeHeapStrings = {
        _dictStringCopyHTHashFunction, /* hash function */
        NULL,                          /* key dup */
        NULL,                          /* val dup */
        _dictStringCopyHTKeyCompare,   /* key compare */
        _dictStringDestructor,         /* key destructor */
        NULL                           /* val destructor */
};

/* This is like StringCopy but also automatically handle dynamic
 * allocated C strings as values. */
dictType dictTypeHeapStringCopyKeyValue = {
        _dictStringCopyHTHashFunction, /* hash function */
        _dictStringDup,                /* key dup */
        _dictStringDup,                /* val dup */
        _dictStringCopyHTKeyCompare,   /* key compare */
        _dictStringDestructor,         /* key destructor */
        _dictStringDestructor,         /* val destructor */
};

int main() {

    const char *private = "xudong";

    dict *db = dictCreate(&dictTypeHeapStrings, (void *)private);

    const char *key = "name";
    const char *value = "xudong";

    dictAdd(db, key, value);
    char *val = (char *)dictFetchValue(db, key);

    for (int i = 0; i < db->ht[0].size; i++) {
        dictEntry *he = db->ht[0].table[i];
        if (!he) continue;
        dictEntry *p = he;
        while (p) {
            if (p->key) printf("%s\n", (char *)p);
            if (p->v.val) printf("%s\n", (char *)p->v.val);
            p = p->next;
        }
    }

    printf("%s\n", val);
    dictPrintStats(db);

    unsigned long i = dictHashKey(db, key);

    printf("%ul\n", i);

    return 0;
}