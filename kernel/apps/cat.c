#include "cat.h"

void cat(string args)
{
    string fileName = splitArg(args, 1);

    ASSERT(strlen(fileName) < MAX_FNAME_LEN);
    catTheFile(finddir_fs(fs_root, fileName));
}


void catTheFile(fs_node_t* fsnode)
{
    newline();
    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        const uint32 rbuff = fsnode->length;
        char buf[rbuff];
        uint32 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
        uint32 j;
        for (j = 0; j < sz; j++)
            printch(buf[j], 0x0F);
        newline();
    }
}

bool findInDictionary(string dictionary,string searchWord)
{
    ASSERT(strlen(dictionary) < MAX_FNAME_LEN);
    if (lookup(finddir_fs(fs_root, dictionary),searchWord))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool lookup(fs_node_t* fsnode,string searchTerm)
{
  searchTerm = toUpper(searchTerm);

  // Current letter and word that we are analyzing
  char curChar;

  if ((fsnode->flags & 0x7) == FS_FILE)
  {
    const uint64 rbuff = fsnode->length;
    char buf[rbuff];
    uint64 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
    uint64 j;

    string curWord = (string) kmalloc(10 * sizeof(char));

    for (j = 0; j < sz; j++)
    {
        print("\nNum: ",0x0D);
        printint(j,0x0F);
        char curCharString[] = { curChar, '\0' };
        curChar = buf[j];

        if (streql(curCharString," "))
        {
            if (streql(curWord,searchTerm))
            {
                return true;
            }
            memset(curWord, '\0', 128);
        }
        else
        {
            strcat(curWord,curCharString);
        }
    }
  }
  return false;
}
