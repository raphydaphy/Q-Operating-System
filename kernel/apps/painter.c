#include "painter.h"

uint8 paintX;
uint8 paintY;

void welcomeToPainter()
{
    paintX = sw / 2;
    paintY = sh / 2;

    paintScreen(screen_color);
    drawFrame(header_background, 0, 0, 80, 4);
    printAt("Q OS Drawing Application\r\n", header_foreground, 1, 1);
    printAt("Dumb Drawing App for Q OS by Raph Hennessy",desc_foreground,1,2);
    drawBorder(screen_background, 0, 4, 80, sh - 1);
}

// for an easy way to exit the program using return;
// I made it an int type function yay :)
int painter(string args)
{
    if (streql(splitArg(args, 1), "-H"))
    {
        print("\nPainter is a simple drawing app for Q OS\nTo use it, type 'painter' on the command line.\nUse the arrow keys to draw lines on your screen.\nPress the spacebar to reset your drawing.",red);
    }
    else
    {
        welcomeToPainter();

        while (true)
        {

            if (paintX < 1)
            {
                paintX = 1;
            }
            else if (paintX > 78)
            {
                paintX = 78;
            }

            if (paintY < 5)
            {
                paintY = 5;
            }
            else if (paintY > 23)
            {
                paintY = 23;
            }

            printAt("*",yellow,paintX,paintY);

            int key = getKeycode() / KC_MAGIC_VAL;

            switch (key)
            {
                case 1:
                    // Escape Pressed
                    clearScreen();
                    return 0;
                    break;
                case 72:
                    // Up Arrow Pressed
                    printAt("*",black,paintX,paintY);
                    paintY--;
                    break;
                case -54:
                    // Up Arrow Released
                    break;
                case 80:
                    // Down Arrow Pressed
                    printAt("*",black,paintX,paintY);
                    paintY++;
                    break;
                case -46:
                    // Down Arrow Released
                    break;
                case 75:
                    // Left Arrow Pressed
                    printAt("*",black,paintX,paintY);
                    paintX--;
                    break;
                case -51:
                    // Left Arrow Released
                    break;
                case 77:
                    // Right Arrow Pressed
                    printAt("*",black,paintX,paintY);
                    paintX++;
                    break;
                case -49:
                    // Right Arrow Released
                    break;
                case 57:
                    // Spacebar Pressed
                    welcomeToPainter();
                    break;
                case -70:
                    // Spacebar Released
                    break;
                default:
                    break;
            }
        }
    }


    return 0;

}
