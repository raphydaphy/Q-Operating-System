#ifndef APP_STACKVM_H
#define APP_STACKVM_H

#include "../inc/qdio.h"

typedef struct {
    list_t istack;
    map_t  varmap;
} stackVM_t;

typedef enum {
    EOS = 0x00, // End of stream
    NOP = 0x01, // Nothing
    pushi = 0x02, // val
    pushd = 0x03, // int, point
    swap = 0x04 // None
} STACKVM_OP;

#define EXEC_SUCCESS 0

stackVM_t initEnv(uint16);

uint32 invokeOp(stackVM_t*, int[], bool);

#endif
