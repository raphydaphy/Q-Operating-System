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

      if (curCharInt == 32)
      {
        newline();
        if (strEql(curWord,searchTerm))
        {
          print("Found Search Word: ",0x04);
          print("",0x07);
        }
        else
        {
          print("Current Word: ",0x04);
          print(curWord,0x0A);
        }
        memset(curWord, '\0', dictionaryLength);
        newline();
      }
      else
      {
        strcat(curWord,curCharString);
        //print(curCharString,0x0E);
      }
    }
  }
  newline();
}
