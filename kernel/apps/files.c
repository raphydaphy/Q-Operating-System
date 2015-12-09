#include "files.h"

void files(string args)
{
    newline();
    if (streql(args," -h"))
    {
      print ("Showing Help for files:", grey);
      print ("\nThe 'files' command will show you the files and folders in your current working directory.",grey);
    }
    else if (streql(args, "") || streql(args, " "))
    {
        // list the contents of
        int i = 0;
        struct dirent *node = 0;
        while ((node = readdir_fs(fs_root, i)) != 0)
        {
            fs_node_t *fsnode = finddir_fs(fs_root, node->name);

            if ((fsnode->flags & 0x7) == FS_DIRECTORY)
            {
                print("dir \t", white);
                print(node->name, white);
                printch('/', white);
            }
            else
            {
                print("file\t", white);
                print(node->name, white);
            }
            newline();
            i++;
        }
    }
}
