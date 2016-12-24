#include "adlist.h"

#include <stdio.h>

void print(void *value) {
    int e = *((int *)value);
    printf("%d\n", e);
}

int main() {
    list *l = listCreate();
    listSetDumpMethod(l, print);

    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; ++i) {
        l = listAddNodeTail(l, array+i);
    }
    printf("list length is %d\n", listLength(l));
    listDump(l);
    listRotate(l);
    listDump(l);
    listRotate(l);
    listDump(l);
    listRotate(l);
    listDump(l);
    listRotate(l);
    listDump(l);
    listRelease(l);
    return 0;
}