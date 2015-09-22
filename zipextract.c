#include "zipextract.h"

char* zipextract(const char *filename, zipextract_callback wirte_callback) {
    char *errstr = NULL;
    void *rawdata = NULL;

    unzFile zfile = unzOpen(filename);
    if (zfile == NULL) {
        errstr =  "cannot open zip file";
        return errstr;
    }

    unz_global_info globalinfo;
    if (unzGetGlobalInfo(zfile, &globalinfo) != UNZ_OK) {
        errstr =  "cannot get global info in zip file";
        goto EndExtract;
    }

    if (unzGoToFirstFile(zfile) != UNZ_OK) {
        errstr =  "cannot goto first file";
        goto EndExtract;
    }

    unz_file_info fileinfo;

    int rawdata_len = 0;
    char file[256] = {0};
    size_t RAWDATA_LEN = 2*1024*1024;

    rawdata = malloc(RAWDATA_LEN);
    if (rawdata == NULL) {
        errstr = "cannot malloc mem";
        goto EndExtract;
    }

    for (int i = 0; i < globalinfo.number_entry; ++i)
    {
        if (unzGetCurrentFileInfo(zfile, &fileinfo, file, sizeof(file), NULL, 0, NULL, 0) != UNZ_OK) {
            errstr = "cannot get global info in zip file";
            goto EndExtract;
        }

        char slash = file[strlen(file)-1];
        if (slash == '\\' || slash == '/') {
            errstr = wirte_callback(ZIPExtra_DIR, file, NULL, 0);
            if (errstr != NULL)
                 goto EndExtract;
        } else {
            if (unzOpenCurrentFile(zfile) != UNZ_OK) {
                errstr =  "cannot OpenCurrentFile";
                goto EndExtract;
            }

            rawdata_len = 0;
            do {
                rawdata_len = unzReadCurrentFile(zfile, rawdata, RAWDATA_LEN);
                if (rawdata_len < 0) {
                    unzCloseCurrentFile(zfile);
                    errstr =  "unzReadCurrentFile failed";
                    goto EndExtract;
                } else if (rawdata_len > 0) {
                    errstr = wirte_callback(ZIPExtra_FILE, file, rawdata, rawdata_len);
                    if (errstr != NULL) {
                        unzCloseCurrentFile(zfile);
                        goto EndExtract;
                    }
                }
            } while(rawdata_len > 0);
            unzCloseCurrentFile(zfile);
        }

        if (i == globalinfo.number_entry-1) {
            break;
        }

        if (unzGoToNextFile(zfile) != UNZ_OK) {
            errstr =  "cannot goto next file";
            goto EndExtract;
        }
    }

EndExtract:
    if (rawdata != NULL)
        free(rawdata);

    unzClose(zfile);
    return errstr;
}
