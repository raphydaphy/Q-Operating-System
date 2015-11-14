#include "inc/kb."
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
    typingCmd = 1;
    newCmd = 1;
    string ch = readStr();
    typingCmd = 0;
    layout = 1;
    if(strEql(ch,"help"))
    {
      print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute",0x0F);
    }
    else if(strEql(ch,"execute"))
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
      if(strEql(tmp,"c"))
      {
	print("\nc>  ",0x0F);
	string c = readStr();
	
      }
      else
      {
	print("The 'do' command does not support the command you entered or it does not exist ",0x0F);
      }
    }
    else if(strEql(ch,"list"))
    {
      print("\nNo Files Found on Disk ",0x0F);
    }
    else if(strEql(ch,"switch"))
    {
      print("\nThe specified directory was not found ",0x0F);
    }
    else if(strEql(ch,"writer"))
    {
      layout = 1;
      clearScreen();
      print("================================================================================\n",0x3F);
      print("                      Q OS Text Editor Version 0.2                              \n",0x3F);
      print("================================================================================\n",0x3F);
      writing = 1;
      layout = 0;
      print(writerContents,0x0F);
      string writerContents = readStr();
    }
    else if(strEql(ch,"clear"))
    {
      clearScreen();
      cursorX = 0;
      cursorY = 0;
      updateCursor();
    }
    else if(strEql(ch,"clear -i"))
    {
      layout = 1;
      clearScreen();
      print("================================================================================\n",0x3F);
      print("                             Welcome to Q OS                                    \n",0x3F);
      print("================================================================================\n",0x3F);
      layout = 0;
    }
    else if(strEql(ch,"newdir"))
    {
      print("\n",0x0F);
    }
    else if(strEql(ch,"erase"))
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
