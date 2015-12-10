#include "skip.h"

void skip(string args) {
    newline();

    string fileToWrite = splitArg(args, 1);
    ASSERT(strlen(fileToWrite) < MAX_FNAME_LEN);
    writeFile(finddir_fs(fs_root, fileToWrite));
}
