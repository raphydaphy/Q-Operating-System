#include "inc/kb.h"
kmain()
{
  layout = 1;
  clearScreen();
  print("================================================================================\n",0x3F);
  print("                             Welcome to Q OS                                    \n",0x3F);
  print("================================================================================\n",0x3F);
  layout = 0;

  while (1)
  {
    layout = 1;
    print("\nQ-Kernel>  ",0x08);
    layout = 0;
    string ch = readStr();
    layout = 1;
    if(strEql(ch,"help "))
    {
      print("\nShowing Help for Q OS \nnano         cd\nls           do",0x0F);
    }
    else if(strEql(ch,"do"))
    {
      print("\n>  ",0x0F);
      string tmp = readStr();
      if(strEql(tmp,"repeat"))
      {
	print("\nrepeat>  ",0x0F);
	string tmp = readStr();
	writing = 1;
	while(1)
	  {
	  printch('\n',0x0F);
	  print(tmp,0x0F);
	}
      }
      if(strEql(tmp,"execute"))
      {
	print("\n",0x0F);
      }
      else
      {
	print("The 'do' command does not support the command you entered or it does not exist ",0x0F);
      }
    }
    else if(strEql(ch,"ls"))
    {
      print("\nNo Files Found on Disk ",0x0F);
    }
    else if(strEql(ch,"cd"))
    {
      print("\nThe specified directory was not found ",0x0F);
    }
    else if(strEql(ch,"writer"))
    {
      layout = 1;
      writing = 1;
      clearScreen();
      cursorX = 0;
      cursorY = 1;
      print("                           Q-OS Text Editor Version 0.2                          ",0x80);
      cursorY - 1;
      cursorX = 0;
      updateCursor();
      print(writerContents,0x0F);
      cursorY = 24;
      cursorX = 0;
      //updateCursor();
      print("                            Press Control to exit                          ",0x80);
      
      cursorX = 0;
      cursorY = 1;
      updateCursor();
      layout = 0;
      string writerContents = readStr();
    }
    else if(strEql(ch,"clear"))
    {
      clearScreen();
    }
    else if(strEql(ch,"sudo"))
    {
      print("\n",0x0F);
    }
    else if(strEql(ch,"exit"))
    {
      print("\n",0x0F);
    }
    else if(strEql(ch,"run"))
    {
      print("\n",0x0F);
    }
    else
    {
      print("\nCommand Not Found ",0x0F);
    }
    print("\n",0x0F);
    layout = 0;
  }
}
