#include "painter.h"

// for an easy way to exit the program using return;
// I made it an int type function yay :)
int painter(string args)
{
    if (streql(splitArg(args, 1), "-H"))
    {
        print("\nPainter is a simple drawing app that dosen't draw... yet",red);
    }
    else if (streql(splitArg(args, 1),"-NEW"))
    {
        while (true)
        {
            int key = getKeycode() / KC_MAGIC_VAL;

            print("\nKeyCode: ",black);
            printint(key,yellow);

            switch (key)
            {
                case 1:
                    // Escape Pressed
                    return 0;
                    break;
                case 72:
                    // Up Arrow Pressed
                    print("\nUp Arrow Pressed",green);
                    break;
                case -54:
                    // Up Arrow Released
                    print("\nUp Arrow Released",red);
                    break;
                case 80:
                    // Down Arrow Pressed
                    print("\nDown Arrow Pressed",green);
                    break;
                case -46:
                    // Down Arrow Released
                    print("\nDown Arrow Released",red);
                    break;
                case 75:
                    // Left Arrow Pressed
                    print("\nLeft Arrow Pressed",green);
                    break;
                case -51:
                    // Left Arrow Released
                    print("\nLeft Arrow Released",red);
                    break;
                case 77:
                    // Right Arrow Pressed
                    print("\nRight Arrow Pressed",green);
                    break;
                case -49:
                    // Right Arrow Released
                    print("\nRight Arrow Released",red);
                    break;
                case 57:
                    // Spacebar Pressed
                    print("\nSpacebar Pressed",green);
                    break;
                case -70:
                    // Spacebar Released
                    print("\nSpacebar Released",red);
                    break;
                default:
                    break;
            }
        }
    }
    else if (streql(splitArg(args, 1),""))
    {
        while (true)
        {
            // 0x01     : ESCAPE    : Exit the progarm
            // 0x4E     : NUMPAD 6  : Move Cursor Right
            // 0x38     : SPACE BAR : Do Nothing Atm :)

            int key = waitUntilKey(3, 0x01, 0x4E, 0x38);

            printint(key,red);

            switch (key)
            {
                case 0x01:
                    return 0;
                    break;
                case 0x4E:
                    print("OMG!",yellow);
                    break;
                default:
                    break;
            }
        }
    }


    return 0;

}
