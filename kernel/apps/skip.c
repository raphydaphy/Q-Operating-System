#include "skip.h"

void skip(string args) {
    newline();

    string fileToWrite = splitArg(args, 1);
    ASSERT(strlen(fileToWrite) < MAX_FNAME_LEN);
    writeFile(finddir_fs(fs_root, fileToWrite));

    newline();

    string buf = "";
    print("Enter your password to unlock Q OS:  ",red);
    readStr(buf,128,true);
    print("\nYou Entered:  ",red);
    print(buf,green);
}
