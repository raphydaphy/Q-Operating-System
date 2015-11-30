#include "skip.h"

void skip(string args) {
    newline();
    /*print("You have entered the ",0x03);
    print("skip",0x04);
    print(" command with the",0x03);
    print(args,0x04);
    print(" argument.",0x03);
    printhex(args,0x0F);*/

    /*for(int i = 0; i < 1; i++){
        for(int j = 0; j < 64; j++){
	    if(&args[i][j] != 32 && &args[i][j] != 0 && &args[i][j] != 10)
	        print((char)&args[i][j],0x0F);
	    else if(&args[i][j] == 32 || &args[i][j] == 0 || &args[i][j] == 10)
		continue;
	    print(" | ",0x0F);
	}
	args++;
	print("\n", 0x0F);
    }*/
    print(splitArg(args, 1),0x0F); //Argument starts from 1
    //splitArg(args,1);
    newline();
    print("\n",0x0F);
    //splitArg(args,2);
    print(splitArg(args, 2),0x0F); //Argument starts from 1
}
