#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcmpr(const void *a, const void *b) { return strcmp(*(char **)a, *(char **)b); }

int main(int argc, char **argv)
{
    qsort(&argv[1], argc - 1, sizeof(char *), strcmpr);
    for (size_t i = 1; i < argc; i++) printf("%s ", argv[i]);
}
