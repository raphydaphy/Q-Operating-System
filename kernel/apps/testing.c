#include "testing.h"

void test(string args) {
    if(streql(args, " -list"))//For testing lists
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

        println("Done sizing up", white);
        printint(test_list.capt, white);

        element_t t;
        for(uint8 i = 0; i < 64; i++) {
            t = list_shift(&test_list);
        }
        println("\nLast item deleted should be \"16\"", white);
        println(t.udata.strdata, white);
        println("\nDeleting all but element \"Pointless\"", white);
        for(uint8 i = 0; i < test_list.size; i++)
            println(list_get(test_list, i), white);
        println("Done resizing up", white);
        printint(test_list.capt, white);
        list_destroy(&test_list);
    }
    else if(streql(args," -set"))
    {
        set_t test_set = set_init();
        for(uint8 i = 0; i < 4; i++) {
            set_add(&test_set, "0");
            set_add(&test_set, "1");
            set_add(&test_set, "2");
            set_add(&test_set, "3");
            set_add(&test_set, "4");
            set_add(&test_set, "5");
            set_add(&test_set, "6");
            set_add(&test_set, "7");
            set_add(&test_set, "8");
            set_add(&test_set, "9");
            set_add(&test_set, "10");
            set_add(&test_set, "11");
            set_add(&test_set, "12");
            set_add(&test_set, "13");
            set_add(&test_set, "14");
            set_add(&test_set, "15");
            set_add(&test_set, "16");
            print("\nIteration: ", white);
            printint(i, white);
        }
        println("\n\nInsertion::Output should be 17", white);
        printint(test_set.size, white);

        set_t tmp = set_init();
        set_add(&tmp, "Union item");
        set_union(&test_set, &tmp);
        println("\n\nUnion::Output should be 18", white);
        printint(test_set.size, white);

        set_intersect(&test_set, &tmp);
        println("\n\nIntersect::Output should be 1", white);
        printint(test_set.size, white);

        println("\n\nPreparing for diff test", white);
        set_add(&test_set, "1");
        set_add(&test_set, "2");
        set_add(&test_set, "3");
        set_add(&tmp, "2");
        set_add(&tmp, "3");
        set_add(&tmp, "4");
        set_diff(&test_set, &tmp);
        println("Diff::Output should be 2", white);
        printint(test_set.size, white);

        set_destroy(&tmp);
        set_destroy(&test_set);
    }
    else if(streql(args, " -strb"))
    {
        static const string bak = "Hello, world ";
        static const uint32 bln = 13;
        strbuilder_t test_strb = strbuilder_init();

        strbuilder_append(&test_strb, bak);
        strbuilder_append(&test_strb, "Hello, 2nd world");
        println("\nTesting backup text. Output should 1", white);
        printint(streql(bak, test_strb.prevTxt), white);
        println("\nOutput should be \"Hello, world Hello, 2nd world\"", white);
        println(strbuilder_tostr(test_strb), white);
        println("\nRemoving greeters from first world", white);
        strbuilder_delete(&test_strb, 0, bln);
        println("\nOutput should be \"Hello, 2nd world\"", white);
        println(strbuilder_tostr(test_strb), white);
        strbuilder_flip(&test_strb);
        println("\nOutput should be \"dlrow dn2 ,olleH\"", white);
        println(strbuilder_tostr(test_strb), white);
    }
    else if(streql(args," -y"))
    {
       //getTime() test
       printint(getTime("year"),white);
    }
}
