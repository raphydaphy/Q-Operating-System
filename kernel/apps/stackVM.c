#include "stackVM.h"

stackVM_t initEnv(uint16 stackSize)
{
    stackVM_t env;
    env.maxsize = stackSize;
    env.istack = list_init_s(stackSize);
    env.varmap = hashmap_init();
    env.status = EXEC_SUCCESS;
    return env;
}

void cleanEnv(stackVM_t* env)
{
    list_destroy(&(env->istack));
    hashmap_destroy(&(env->varmap));
    env->istack = list_init_s(env->maxsize);
    env->varmap = hashmap_init();
    env->status = EXEC_SUCCESS;
}

uint32 invokeOp(stackVM_t* env, int opcodes[])
{
    int opIndex = 0;
    int currentOp = NOP;
    list_t tryCatchNests = list_init();
    map_t jmpPoints = hashmap_init();

start:
    while(env->status == EXEC_SUCCESS)
    {
        currentOp = opcodes[opIndex++];
        switch(currentOp)
        {
        case NOP:
            continue;
        case EOS:
            env->status = EXEC_SUCCESS;
            goto end;
        case setl:
        {
            int param1 = opcodes[opIndex++];
            hashmap_add(&jmpPoints, itos10(param1), makeIntElement(opIndex));
            break;
        }
        case seto:
        {
            int param1 = opcodes[opIndex++];
            int param2 = opcodes[opIndex++];
            hashmap_add(&jmpPoints, itos10(param1), makeIntElement(opIndex + param2));
            break;
        }
        case defi:
        {
            int param1 = opcodes[opIndex++];
            int tail = etoi(list_remove(&(env->istack), env->istack.size - 1));
            hashmap_add(&(env->varmap), itos10(param1), makeIntElement(tail));
            break;
        }
        case deff:
        {
            int param1 = opcodes[opIndex++];
            float tail = etoi(list_remove(&(env->istack), env->istack.size - 1));
            hashmap_add(&(env->varmap), itos10(param1), makeFloatElement(tail));
            break;
        }
        case geti:
        {
            int param1 = opcodes[opIndex++];
            int i = etoi(hashmap_getVal(env->varmap, itos10(param1)));
            list_addi(&(env->istack), i);
            break;
        }
        case getf:
        {
            int param1 = opcodes[opIndex++];
            float f = etof(hashmap_getVal(env->varmap, itos10(param1)));
            list_addf(&(env->istack), f);
            break;
        }
        case jmpl:
        {
            int param1 = opcodes[opIndex++];
            element_t jmpIndex = hashmap_getVal(jmpPoints, itos10(param1));
            if(jmpIndex.ctype != INT)
            {
                env->status = ILLEGAL_JOFF;
            }
            else
            {
                opIndex = etoi(jmpIndex);
            }
            break;
        }
        case jmpz:
        {
            int param1 = opcodes[opIndex++];
            if(param1 < 0)
            {
                env->status = ILLEGAL_JOFF;
            }
            else
            {
                opIndex = param1;
            }
            break;
        }
        case jmpo:
        {
            int param1 = opcodes[opIndex++];
            opIndex += param1;
            break;
        }
        case ifjl:
        {
            int param1 = opcodes[opIndex++];
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            if(tail.udata.intdata)
            {
                element_t jmpIndex = hashmap_getVal(jmpPoints, itos10(param1));
                if(jmpIndex.ctype != INT)
                {
                    env->status = ILLEGAL_JOFF;
                }
                else
                {
                    opIndex = etoi(jmpIndex);
                }
            }
            break;
        }
        case ifjz:
        {
            int param1 = opcodes[opIndex++];
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            if(tail.udata.intdata)
            {
                if(param1 < 0)
                {
                    messageBox("\x01 Jumping to negative offset");
                    env->status = ILLEGAL_JOFF;
                }
                else
                {
                    opIndex = param1;
                }
            }
            break;
        }
        case ifjo:
        {
            int param1 = opcodes[opIndex++];
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            if(tail.udata.intdata)
            {
                opIndex += param1;
            }
            break;
        }
        
        case tryl:
        {
            int param1 = opcodes[opIndex++];
            list_addi(&tryCatchNests, param1);
            break;
        }
        case tryd:
        {
            if(tryCatchNests.size == 0)
            {
                env->status = ILLEGAL_TRYB;
            }
            else
            {
                list_remove(&tryCatchNests, tryCatchNests.size - 1);
            }
            break;
        }
        case pushi:
        {
            int param1 = opcodes[opIndex++];
            list_addi(&(env->istack), param1);
            break;
        }
        case pushf:
        {
            string param1 = (string) kmalloc(39 * sizeof(char));
            strcat(param1, itos10(opcodes[opIndex++]));
            strcat(param1, ".");
            strcat(param1, itos10(opcodes[opIndex++]));
            list_addf(&(env->istack), (float) stod(param1));
            break;
        }
        case pushs:
        {
            int param1 = opcodes[opIndex++];
            list_adds(&(env->istack), (string) param1);
            break;
        }
        case addi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata += etoi(tail);
            break;
        }
        case addf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata += etof(tail);
            break;
        }
        case subi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata -= etoi(tail);
            break;
        }
        case subf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata -= etof(tail);
            break;
        }
        case muli:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata *= etoi(tail);
            break;
        }
        case mulf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.floatdata *= etof(tail);
            break;
        }
        case divi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int tmp = etoi(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
            } else {
                ntail->udata.intdata /= tmp;
            }
            break;
        }
        case divf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            float tmp = etof(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
            } else {
                ntail->udata.floatdata /= tmp;
            }
            break;
        }
        case modi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int tmp = etoi(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
            } else {
                ntail->udata.intdata %= tmp;
            }
            break;
        }
        case sftl:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata <<= etoi(tail);
            break;
        }
        case sftr:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata >>= etoi(tail);
            break;
        }
        case andb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata &= etoi(tail);
            break;
        }
        case orb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata |= etoi(tail);
            break;
        }
        case xorb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata ^= etoi(tail);
            break;
        }
        case notb:
        {
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = ~ntail->udata.intdata;
            break;
        }
        case _hlt:
            __asm__ __volatile__("hlt");
            break;
        case _cli:
            __asm__ __volatile__("cli");
            break;
        case _sti:
            __asm__ __volatile__("sti");
            break;
        case raddi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int left = ntail->udata.intdata;
            ntail->udata.intdata = addRange(left, etoi(tail));
            break;
        }
        case rsubi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int left = ntail->udata.intdata;
            ntail->udata.intdata = subRange(left, etoi(tail));
            break;
        }
        case ci_f:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == INT)
            {
                int f = etoi(*tail);
                tail->ctype = FLT;
                tail->udata.floatdata = (float) f;
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case cf_i:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == FLT)
            {
                float f = etof(*tail);
                tail->ctype = INT;
                tail->udata.intdata = (int) f;
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case cs_i:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == STR)
            {
                string s = etos(*tail);
                tail->ctype = INT;
                tail->udata.intdata = stoc(s);
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case cf_s:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == FLT)
            {
                float f = etof(*tail);
                tail->ctype = STR;
                tail->udata.strdata = ftos(f);
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case ci_s:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == INT)
            {
                int i = etoi(*tail);
                tail->ctype = STR;
                tail->udata.strdata = itos10(i);
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case ei_s:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == INT)
            {
                int i = etoi(*tail);
                tail->ctype = STR;
                tail->udata.strdata = itos64(i);
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case ci_p:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == INT)
            {
                int addr = etoi(*tail);
                tail->ctype = STR;
                tail->udata.strdata = (string) addr;
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case cs_p:
        {
            element_t* tail = &(env->istack.data[env->istack.size - 1]);
            if(tail->ctype == STR)
            {
                string s = etos(*tail);
                tail->ctype = INT;
                tail->udata.intdata = (int) ((void*) s);
            }
            else
            {
                env->status = BAD_CONV_TYP;
            }
            break;
        }
        case swap:
        {
            element_t tail = env->istack.data[env->istack.size - 1];
            element_t tmp = env->istack.data[env->istack.size - 2];
            env->istack.data[env->istack.size - 2] = tail;
            env->istack.data[env->istack.size - 1] = tmp;
            break;
        }
        case clrs:
            list_destroy(&(env->istack));
            env->istack = list_init_s(env->maxsize);
            break;
        case flip:
            list_flip(&env->istack);
            break;
        case pop:
            if(env->istack.size > 0)
            {
                list_remove(&(env->istack), env->istack.size - 1);
            }
            break;
        case popc:
        {
            int param1 = opcodes[opIndex++];
            while(param1-- > 0)
            {
                if(env->istack.size == 0) // Its unsigned
                {
                    break;
                }
                list_remove(&(env->istack), env->istack.size - 1);
            }
            break;
        }
        case putf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            printf("%f", etof(tail));
            break;
        }
        case puti:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            printf("%d", etoi(tail));
            break;
        }
        case putc:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            printf("%c", etoi(tail));
            break;
        }
        case puts:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            printf(etos(tail));
            break;
        }
        case thrwi:
        {
            int param1 = opcodes[opIndex++];
            // No error when throw code is invalid
            param1 = param1 < UNDEF_EXCEPT ? param1 : UNDEF_EXCEPT;
            env->status = param1;
            break;
        }
        case cmpt:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = ntail->ctype == tail.ctype;
            break;
        }
        case eqlv:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            rehash(ntail);
            rehash(&tail);
            ntail->udata.intdata = eqlElement_t(*ntail, tail);
            break;
        }
        case cmpv:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            rehash(ntail);
            rehash(&tail);
            ntail->udata.intdata = cmpElement_t(*ntail, tail);
            break;
        }
        case inb:
        {
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = inportb((uint16) ntail->udata.intdata);
            break;
        }
        case outb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t ntail = list_remove(&(env->istack), env->istack.size - 1);
            outportb((uint16) tail.udata.intdata, (uint8) ntail.udata.intdata);
            break;
        }
        case outw:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t ntail = list_remove(&(env->istack), env->istack.size - 1);
            outportw((uint16) tail.udata.intdata, (uint8) ntail.udata.intdata);
            break;
        }
        case blnk:
            clearScreen();
            break;
        case infbf:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            messageBox(ftos(etof(tail)));
            break;
        }
        case infbi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            messageBox(itos10(etoi(tail)));
            break;
        }
        case infbc:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            string msg = " ";
            msg[0] = (char) etoi(tail);
            messageBox(msg);
            break;
        }
        case infbs:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            string msg = etos(tail);
            messageBox(msg);
            break;
        }
        case dup:
        {
            element_t tail = env->istack.data[env->istack.size - 1];
            list_adde(&(env->istack), tail);
            break;
        }
        default:
            env->status = ILLEGAL_OPND;
        }
    }

    if (tryCatchNests.size > 0)
    {
        int jmpLbl = etoi(list_remove(&(tryCatchNests), tryCatchNests.size - 1));
        element_t jmpIndex = hashmap_getVal(jmpPoints, itos10(jmpLbl));
        if(jmpIndex.ctype != INT)
        {
            env->status = ILLEGAL_JOFF;
        }
        else
        {
            opIndex = etoi(jmpIndex);
            list_addi(&(env->istack), env->status);
            env->status = EXEC_SUCCESS;
            // This means the cycle starts again... more spaghetti
            goto start;
        }
    }

end: // Once again... I am sorry for this spaghetti business
    return env->status;
}

