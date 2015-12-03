#include "testing.h"

void test(string args) {
    if(strEql(args, " -list"))//For testing lists
    {
        newline();
        list_t test_list = list_init();
        test_list.autoShrink = true;

        for(uint8 i = 0; i < 4; i++) {
            list_add(&test_list, "1");
            list_add(&test_list, "2");
            list_add(&test_list, "3");
            list_add(&test_list, "4");
            list_add(&test_list, "5");
            list_add(&test_list, "6");
            list_add(&test_list, "7");
            list_add(&test_list, "8");
            list_add(&test_list, "9");
            list_add(&test_list, "10");
            list_add(&test_list, "11");
            list_add(&test_list, "12");
            list_add(&test_list, "13");
            list_add(&test_list, "14");
            list_add(&test_list, "15");
            list_add(&test_list, "16");
        }
        list_add(&test_list, "Pointless");

        println("Done sizing up", 0x0F);
        printint(test_list.capt, 0x0f);

        for(uint8 i = 0; i < 64; i++){
            list_shift(&test_list);
        }
        newline();
        println("Deleting all but element \"Pointless\"", 0x0F);
        for(uint8 i = 0; i < test_list.size; i++)
            println(list_get(test_list, i), 0x0F);
        println("Done resizing up", 0x0F);
        printint(test_list.capt, 0x0f);
        
        list_destroy(&test_list);
    }
    else if(strEql(args," -y"))
    {
       //getTime() test
       printint(getTime("year"),0x0F);
    }
}
