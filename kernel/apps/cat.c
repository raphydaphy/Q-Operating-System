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

bool findInDictionary(fs_node_t* fsnode,int dictionaryLength,string searchTerm)
{
  newline();
  print(searchTerm,0x09);

  // Current letter and word that we are analyzing
  char curChar;
  int curCharInt = 0;

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
        if (strEql(curWord,searchTerm))
        {
            // The curWord string now stores the word we were looking for
            return true;
        }
        else
        {
          return false;
        }
        memset(curWord, '\0', dictionaryLength);
      }
      else
      {
        strcat(curWord,curCharString);
      }
    }

    return false;
  }
}
