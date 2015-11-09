#include "inc/screen.h"
#include "inc/kb.h"
kmain()
{
  clearScreen();
  print("================================================================================\n",0x0F);
  print("                             Welcome to Q OS\n\n",0x0F);
  print("================================================================================\n",0x0F);

  while (1)
  {
    print("\nQ-Kernel>  ",0x0F);

    string ch = readStr();
    if(strEql(ch,"help "))
    {
      print("\nShowing Help for Q OS ",0x0F);
    }
    else if(strEql(ch,"do "))
    {
      print("\n>  ",0x0F);
      string tmp = readStr();
      if(strEql(tmp,"repeat"))
      {
	print("\nrepeat>  ",0x0F);
	string tmp = readStr();
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
    else if(strEql(ch,"ls "))
    {
      print("\nNo Files Found on Disk ",0x0F);
    }
    else if(strEql(ch,"cd "))
    {
      print("\nThe specified directory was not ound ",0x0F);
    }
    else if(strEql(ch,"nano "))
    {
      clearScreen();
      print("                        Q-OS Nano Text Editor Version 0.1                        ",0xF0);
      print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",0x0F);
      print("                         Built for Q-OS by Raph Hennessy                        ",0xF0);
      
      cursorX = 0;
      cursorY = 1;
      updateCursor();
      readStr();
    }
    else if(strEql(ch,"cat"))
    {
      print("\n",0x0F);
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
  }
}
