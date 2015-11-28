#include "files.h"

void files(string args)
{
    newline();
    if (strEql(args," -h"))
    {
      print ("Showing Help for files:", 0x03);
      print ("\nThe 'files' command will show you the files and folders in your current working directory.",0x03);
    }
    else if (strEql(args, "") || strEql(args, " "))
    {
        // list the contents of
        int i = 0;
        struct dirent *node = 0;
        while ((node = readdir_fs(fs_root, i)) != 0)
        {
            fs_node_t *fsnode = finddir_fs(fs_root, node->name);

            if ((fsnode->flags & 0x7) == FS_DIRECTORY)
            {
                print("dir \t", 0x0F);
                print(node->name, 0x0F);
                printch('/', 0x0F);
            }
            else
            {
                print("file\t", 0x0F);
                print(node->name, 0x0F);
            }
            newline();
            i++;
        }
    }
}
