#ifndef APP_STACKVM_H
#define APP_STACKVM_H

#include "../inc/qdio.h"

typedef struct {
    list_t istack;
    map_t  varmap;
    uint16 status;
    uint16 maxsize;
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
    divd = 0x14,    // None
    modi = 0x15,    // None; Also modd does not exist!
    raddi = 0x16,   // None; 1, 5 -> 1+...+5
    rsubi = 0x17,   // None; 1, 5 -> 1-...-5
    clrs = 0x18,    // None; Clears the stack
    flip = 0x19     // None; Flips the stack
} STACKVM_OP;

typedef enum {
    EXEC_SUCCESS = 0,
    ILLEGAL_OPND = 1,
    DIVI_BY_ZERO = 2
} statusCode;

stackVM_t initEnv(uint16);

void cleanEnv(stackVM_t*);

uint32 invokeOp(stackVM_t*, int[], bool);

#endif
