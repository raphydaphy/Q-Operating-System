#include "actparse.h"

string parse(string input) {
    // { intrusion2, entrance,@ (entrance by force or without permission or welcome) }
    // { [ attainment, verb.social:attain,+ ] accomplishment,@ (the act of achieving an aim; "the attainment of independence") }
    strbuilder_t stb = strbuilder_init();
    strbuilder_appends(&stb, strTrim(input));
    if (strbuilder_head(stb) == '{' && strbuilder_tail(stb) == '}') {
        strbuilder_delete(&stb, 0, 1);
        strbuilder_delete(&stb, stb.size - 1, stb.size);
        strbuilder_trim(&stb);
    } else return "";
    return strbuilder_tostr(stb);
}
