#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *basename_const(const char *p)
{
    static char *buf = NULL;
    static size_t buf_size = 0;
    size_t len;

    len = strlen(p);
    if (len + 1 > buf_size) {
        if ((buf = realloc(buf, len + 1)) == NULL) {
            perror("basename_const: realloc failed");
            return NULL;
        }
    }

    strcpy(buf, p);

    return basename(buf);
}

char *dirname_const(const char *p)
{
    static char *buf = NULL;
    static size_t buf_size = 0;
    size_t len;

    len = strlen(p);
    if (len + 1 > buf_size) {
        if ((buf = realloc(buf, len + 1)) == NULL) {
            perror("dirname_const: realloc failed");
            return NULL;
        }
    }

    strcpy(buf, p);

    return dirname(buf);
}
