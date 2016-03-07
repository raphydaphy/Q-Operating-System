#include "files.h"

void files(string args)
{
    newline();

    if (streql(splitArg(args, 1), "-H"))
    {
        print ("Showing Help for files:", black);
        print ("\nThe 'files' command will show you the files and folders in your current working directory.", black);
    }
    else if (streql(splitArg(args, 1), "ME/") || streql(splitArg(args, 1), "ME"))
    {
        // list the contents of the 'me' directory
        int i = 0;
        struct dirent *node = 0;
        while ((node = readdir_fs(fs_root, i)) != 0)
        {
            if (node->name[0] == 'm' && node->name[1] == 'e')
            {
                // this is probably a file required for `me` so we will show it
                print("file\t",green);
                print(node->name, magenta);
                newline();
            }
            i++;
        }
    }
    else
    {
        // list the contents of
        int i = 0;
        struct dirent *node = 0;

        // display the `me` directory even thoughh it dosen't exist
        print("dir \t",green);
        print("me/",magenta);
        newline();

        while ((node = readdir_fs(fs_root, i)) != 0)
        {
            // create a variable to store the selected file
            fs_node_t *fsnode = finddir_fs(fs_root, node->name);

            // if the file is a directory
            if ((fsnode->flags & 0x7) == FS_DIRECTORY)
            {
                print("dir \t", green);
                print(node->name, magenta);
                printch('/', magenta);

                newline();
            }
            else
            {
                // If the file does not begin with 'me'
                if (node->name[0] != 'm' && node->name[1] != 'e')
                {
                    print("file\t", green);
                    print(node->name, magenta);
                    newline();
                }
            }
            i++;
        }
    }
}
