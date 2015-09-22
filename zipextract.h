#ifndef ZIPEXTRACT
#define ZIPEXTRACT

#include <errno.h>
#include <zlib.h>

#include "unzip.h"

#define ZIPExtra_DIR    0
#define ZIPExtra_FILE   1

typedef char*(*zipextract_callback)(int filetype, const char *filename, void *data, size_t datasz);

char* zipextract(const char *filename, zipextract_callback wirte_callback);

#endif // ZIPEXTRACT

