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

	// Current letter and word that we are analyzing
    char* curChar;
	char* curWord = "";

    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        const uint32 rbuff = fsnode->length;
        char buf[rbuff];
        uint32 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
        uint32 j;
        for (j = 0; j < sz; j++)
        {
            print("So Far So Gud",0x0E);
            curChar = buf[j];
            if (strEql(curChar," "))
			{
				// The curWord value now stores the next word in the dictionary so now we can see if the word
                //we are looking for is the same as the one we are currently on...
				for(uint8 tmp = 0; tmp < dictionaryLength; tmp++)
				{
                    printint(tmp,0x0D);
					if (strEql(curWord,searchTerm))
					{
						print("We found the word in the dictionary!",0x0D);
						return true;
                    }
				}
				curWord = "";
			}
			else
			{
				strcat(curWord,curChar);
			}
        }
        newline();
    }
}
