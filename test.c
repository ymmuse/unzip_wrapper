#include <stdio.h>
#include "zipextract.h"


char* extract_callback(int filetype, const char *filename, void *data, size_t sz) {
    if (filetype == ZIPExtra_DIR) {
        printf("#dir %s, 0\n", filename);
    } else {
        printf("#file %s, %d\n", filename, sz);
    }
    return NULL;
}

int main(void)
{
    char *error = zipextract("test.zip", extract_callback);
    if (error != NULL)
        printf("%s\n", error);
    return 0;
}

