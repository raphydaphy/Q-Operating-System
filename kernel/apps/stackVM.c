#include "stackVM.h"

stackVM_t initEnv(uint16 stackSize)
{
    stackVM_t env;
    env.istack = list_init_s(stackSize);
    env.varmap = hashmap_init();
    env.status = EXEC_SUCCESS;
    return env;
}

void cleanEnv(stackVM_t* env)
{
    uint16 oldCapt = env->istack.capt;
    list_destroy(&(env->istack));
    hashmap_destroy(&(env->varmap));
    env->istack = list_init_s(oldCapt);
    env->varmap = hashmap_init();
    env->status = EXEC_SUCCESS;
}

uint32 invokeOp(stackVM_t* env, int opcodes[], bool debug)
{
    int opIndex = 0;
    int currentOp = NOP;

    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);
    drawFrame(blue, 0, 0, sw, sh - 1);

    while(env->status == EXEC_SUCCESS)
    {
        currentOp = opcodes[opIndex++];
        switch(currentOp)
        {
        case NOP:
            if(debug)
            {
                messageBox("No operation!");
            }
            continue;
        case EOS:
            messageBox("Done!!!");
            env->status = EXEC_SUCCESS;
            break;
        case pushi:
        {
            int param1 = opcodes[opIndex++];
            list_addi(&(env->istack), param1);
            if(debug)
            {
                messageBox("Pushed int");
                messageBox(itos10(list_taili(env->istack)));
            }
            break;
        }
        case pushd:
        {
            string param1 = (string) kmalloc(39 * sizeof(char));
            strcat(param1, itos10(opcodes[opIndex++]));
            strcat(param1, ".");
            strcat(param1, itos10(opcodes[opIndex++]));
            list_addf(&(env->istack), (float) stod(param1));
            if(debug)
            {
                messageBox("Pushed double");
                messageBox(ftos(list_tailf(env->istack)));
            }
            break;
        }
        case addi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata += etoi(tail);
            if(debug)
            {
                messageBox("i index(last) + index(last - 1)");
            }
            break;
        }
        case addd:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata += etof(tail);
            if(debug)
            {
                messageBox("f index(last) + index(last - 1)");
            }
            break;
        }
        case subi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata -= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) - index(last - 1)");
            }
            break;
        }
        case subd:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata -= etof(tail);
            if(debug)
            {
                messageBox("f index(last) - index(last - 1)");
            }
            break;
        }
        case muli:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata *= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) * index(last - 1)");
            }
            break;
        }
        case muld:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata *= etof(tail);
            if(debug)
            {
                messageBox("f index(last) * index(last - 1)");
            }
            break;
        }
        case divi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int tmp = etoi(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
                messageBox("\x01 Divide by zero");
            } else {
                ntail->udata.intdata /= tmp;
                if(debug)
                {
                    messageBox("i index(last) / index(last - 1)");
                }
            }
            break;
        }
        case divd:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            float tmp = etof(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
                messageBox("\x01 Divide by zero");
            } else {
                ntail->udata.floatdata /= tmp;
                if(debug)
                {
                    messageBox("f index(last) / index(last - 1)");
                }
            }
            break;
        }
        case ci_d:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == INT)
            {
                int f = etoi(*tail);
                tail->ctype = FLT;
                if(debug)
                {
                    messageBox("Casted Int to Double");
                }
                tail->udata.floatdata = (float) f;
            }
            break;
        }
        case cd_i:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == FLT)
            {
                float f = etof(*tail);
                tail->ctype = INT;
                if(debug)
                {
                    messageBox("Casted Double to Int");
                }
                tail->udata.intdata = (int) f;
            }
            break;
        }
        case swap:
        {
            element_t tail = env->istack.data[env->istack.size - 1];
            element_t tmp = env->istack.data[env->istack.size - 2];
            env->istack.data[env->istack.size - 2] = tail;
            env->istack.data[env->istack.size - 1] = tmp;
            if(debug)
            {
                messageBox("Swapped");
            }
            break;
        }
        default:
            messageBox("\x01 Illegal opcode");
            if(debug)
            {
                messageBox(itos10(currentOp));
            }
            env->status = ILLEGAL_OPND;
        }
        drawFrame(blue, 0, 0, sw, sh - 1);
        printAt("First Value", black, 2, 4);
        element_t tmp;
        for(uint32 stacki = 0 ; stacki < env->istack.size; stacki++) 
        {
            tmp = env->istack.data[stacki];
            switch(tmp.ctype) {
            case INT:
                printAt("i", black, 2, stacki + 5);
                printAt(itos10(etoi(tmp)), black, 4, stacki + 5);
                break;
            case FLT:
                printAt("f", black, 2, stacki + 5);
                printAt(ftos(etof(tmp)), black, 4, stacki + 5);
                break;
            default: break;
            }
        }
    }
    strcpy(vidmem, oldmem);
    return env->status;
}

