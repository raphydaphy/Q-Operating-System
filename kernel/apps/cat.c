#include "cat.h"

void cat(fs_node_t* fsnode)
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

    ASSERT(strlength(dictionary) < MAX_FNAME_LEN);
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
  newline();
  searchTerm = toUpper(searchTerm);

  // Current letter and word that we are analyzing
  char curChar;
  int curCharInt;

  if ((fsnode->flags & 0x7) == FS_FILE)
  {
    const uint32 rbuff = fsnode->length;
    char buf[rbuff];
    uint32 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
    uint32 j;

    string curWord = kmalloc((4 + 5 + 1) * sizeof(char));

    for (j = 0; j < sz; j++)
    {
        char curCharString[] = { curChar, '\0' };
        curChar = buf[j];
        curCharInt = curChar;

        if (strEql(curCharString," "))
        {
            print(" ",0x0F);
            if (strEql(curWord,searchTerm))
            {
                print(curWord,0x09);
            }
            else
            {
                print(curWord,0x0A);
            }
            memset(curWord, '\0', 128);
        }
        else
        {
            strcat(curWord,curCharString);
        }
    }
  }
  newline();
}
