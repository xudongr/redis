#include "linenoise.h"
#include <stdio.h>

int main() {
    const char *hello = ">";
    char *line;
    line = linenoise(hello);
    printf("%s\n", line);
}