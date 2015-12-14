#ifndef APP_STACKVM_H
#define APP_STACKVM_H

#include "../inc/qdio.h"

typedef struct {
    list_t istack;
    map_t  varmap;
} stackVM_t;

typedef enum {
    EOS = 0x00,     // End of stream
    NOP = 0x01,     // Nothing
    pushi = 0x02,   // val
    pushd = 0x03,   // int, point
    swap = 0x04,    // None
    addi = 0x05,    // None
    addd = 0x06,    // None
    ci_d = 0x07,    // None
    cd_i = 0x08,    // None
    subi = 0x09,    // None
    subd = 0x10,    // None
    muli = 0x11,    // None
    muld = 0x12,    // None
    divi = 0x13,    // None
    divd = 0x14     // None
} STACKVM_OP;

#define EXEC_SUCCESS 0

stackVM_t initEnv(uint16);

uint32 invokeOp(stackVM_t*, int[], bool);

#endif
