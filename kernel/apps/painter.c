#include "painter.h"

void painter(string args)
{
    UNUSED(args);

    printch(getch(),red);

    waitUntilKey(3, 0x15 /*Y*/, 0x31 /*N*/, 0x2E /*C*/);

    bool going = true;
    while (going)
    {
        // 0x01 : ESCAPE : Exit the progarm
        //

        int key = getKeycode() / KC_MAGIC_VAL;

        printint(key,red);

        switch (key)
        {
            case 0x01:
                going = false;
                break;
            default:
                break;
        }
    }

}
