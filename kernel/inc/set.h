#ifndef SET_H
#define SET_H

#include "dynsto.h"

typedef struct {
    element_t* data;
    uint32 capt;
    uint32 size;
    bool autoShrink; // False on default...
    uint32 autoShrinkTrigger;
} set_t;


#endif
