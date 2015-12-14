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

uint32 invokeOp(stackVM_t* env, int opcodes[], bool debug)
{
    int opIndex = 0;
    int currentOp = NOP;
    list_t tryCatchNests = list_init();
    map_t jmpPoints = hashmap_init();

    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);
    drawFrame(blue, 0, 0, sw, sh - 1);

start:
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
            goto end;
        case setl:
        {
            int param1 = opcodes[opIndex++];
            hashmap_add(&jmpPoints, itos10(param1), makeIntElement(opIndex));
            if(debug)
            {
                messageBox("Added jmp point");
            }
            break;
        }
        case seto:
        {
            int param1 = opcodes[opIndex++];
            int param2 = opcodes[opIndex++];
            hashmap_add(&jmpPoints, itos10(param1), makeIntElement(opIndex + param2));
            if(debug)
            {
                messageBox("Added jmp point");
            }
            break;
        }
        case defi:
        {
            int param1 = opcodes[opIndex++];
            int tail = etoi(list_remove(&(env->istack), env->istack.size - 1));
            hashmap_add(&(env->varmap), itos10(param1), makeIntElement(tail));
            if(debug)
            {
                messageBox("i Defined variable");
            }
            break;
        }
        case deff:
        {
            int param1 = opcodes[opIndex++];
            float tail = etoi(list_remove(&(env->istack), env->istack.size - 1));
            hashmap_add(&(env->varmap), itos10(param1), makeFloatElement(tail));
            if(debug)
            {
                messageBox("f Defined variable");
            }
            break;
        }
        case geti:
        {
            int param1 = opcodes[opIndex++];
            int i = etoi(hashmap_getVal(env->varmap, itos10(param1)));
            list_addi(&(env->istack), i);
            if(debug)
            {
                messageBox("i Pushed variable value");
            }
            break;
        }
        case getf:
        {
            int param1 = opcodes[opIndex++];
            float f = etof(hashmap_getVal(env->varmap, itos10(param1)));
            list_addf(&(env->istack), f);
            if(debug)
            {
                messageBox("f Pushed variable value");
            }
            break;
        }
        case jmpl:
        {
            int param1 = opcodes[opIndex++];
            element_t jmpIndex = hashmap_getVal(jmpPoints, itos10(param1));
            if(jmpIndex.ctype != INT)
            {
                messageBox("\x01 Destinated jump point has not been set");
                env->status = ILLEGAL_JOFF;
            }
            else
            {
                opIndex = etoi(jmpIndex);
                if(debug)
                {
                    messageBox("Jumped to jmp point");
                }
            }
            break;
        }
        case jmpz:
        {
            int param1 = opcodes[opIndex++];
            if(param1 < 0)
            {
                messageBox("\x01 Jumping to negative offset");
                env->status = ILLEGAL_JOFF;
            }
            else
            {
                opIndex = param1;
                if(debug)
                {
                    messageBox("Jumped to offset");
                }
            }
            break;
        }
        case jmpo:
        {
            int param1 = opcodes[opIndex++];
            opIndex += param1;
            if(debug)
            {
                messageBox("Jumped to offset");
            }
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
                    messageBox("\x01 Destinated jump point has not been set");
                    env->status = ILLEGAL_JOFF;
                }
                else
                {
                    opIndex = etoi(jmpIndex);
                    if(debug)
                    {
                        messageBox("Jumped to jmp point after condition");
                    }
                }
            }
            else
            {
                if(debug)
                {
                    messageBox("Conditional is false. Ignore jump");
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
                    if(debug)
                    {
                        messageBox("Jumped to offset after condition");
                    }
                }
            }
            else
            {
                if(debug)
                {
                    messageBox("Conditional is false. Ignore jump");
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
                if(debug)
                {
                    messageBox("Jumped to offset after condition");
                }
            }
            else
            {
                if(debug)
                {
                    messageBox("Conditional is false. Ignore jump");
                }
            }
            break;
        }
        
        case tryl:
        {
            int param1 = opcodes[opIndex++];
            list_addi(&tryCatchNests, param1);
            if(debug)
            {
                messageBox("Registered try-catch block");
            }
            break;
        }
        case tryd:
        {
            if(tryCatchNests.size == 0)
            {
                messageBox("\x01 Ending try-catch without head");
            }
            else
            {
                list_remove(&tryCatchNests, tryCatchNests.size - 1);
                if(debug)
                {
                    messageBox("Removed previously defined block");
                }
            }
            break;
        }
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
        case modi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int tmp = etoi(tail);
            if(tmp == 0) {
                env->status = DIVI_BY_ZERO;
                messageBox("\x01 Divide by zero");
            } else {
                ntail->udata.intdata %= tmp;
                if(debug)
                {
                    messageBox("i index(last) % index(last - 1)");
                }
            }
            break;
        }
        case sftl:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata <<= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
            break;
        }
        case sftr:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata >>= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
            break;
        }
        case andb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata &= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
            break;
        }
        case orb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata |= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
            break;
        }
        case xorb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata ^= etoi(tail);
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
            break;
        }
        case notb:
        {
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = ~ntail->udata.intdata;
            if(debug)
            {
                messageBox("i index(last) % index(last - 1)");
            }
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
            if(debug)
            {
                messageBox("i index(last) + ... + index(last - 1)");
            }
            break;
        }
        case rsubi:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            int left = ntail->udata.intdata;
            ntail->udata.intdata = subRange(left, etoi(tail));
            if(debug)
            {
                messageBox("i index(last) - ... - index(last - 1)");
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
        case clrs:
            list_destroy(&(env->istack));
            env->istack = list_init_s(env->maxsize);
            if(debug)
            {
                messageBox("Stack cleared");
            }
            break;
        case flip:
            list_flip(&env->istack);
            if(debug)
            {
                messageBox("Stack reversed");
            }
            break;
        case pop:
            if(env->istack.size > 0)
            {
                list_remove(&(env->istack), env->istack.size - 1);
                if(debug)
                {
                    messageBox("Item was pop-d");
                }
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
            if(debug)
            {
                messageBox("Items were pop-d");
            }
            break;
        }
        case cmpt:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = ntail->ctype == tail.ctype;
            if(debug)
            {
                if(ntail->udata.intdata)
                {
                    messageBox("Type of index(last) index(last - 1) same");
                }
                else
                {
                    messageBox("Type of index(last) index(last - 1) diff");
                }
            }
            break;
        }
        case eqlv:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            rehash(ntail);
            rehash(&tail);
            ntail->udata.intdata = eqlElement_t(*ntail, tail);
            if(debug)
            {
                if(ntail->udata.intdata)
                {
                    messageBox("Val of index(last) index(last - 1) same");
                }
                else
                {
                    messageBox("Val of index(last) index(last - 1) diff");
                }
            }
            break;
        }
        case cmpv:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            rehash(ntail);
            rehash(&tail);
            ntail->udata.intdata = cmpElement_t(*ntail, tail);
            if(debug)
            {
                switch(ntail->udata.intdata)
                {
                case -1:
                    messageBox("Val of index(last) < index(last - 1)");
                    break;
                case 0:
                    messageBox("Val of index(last) = index(last - 1)");
                    break;
                case 1:
                    messageBox("Val of index(last) > index(last - 1)");
                    break;
                default:
                    messageBox("\x02 Illegal state... Please contact one of the\r\ndevs for assitance");
                    break;
                }
            }
            break;
        }
        case inb:
        {
            element_t* ntail = &(env->istack.data[env->istack.size - 1]);
            ntail->udata.intdata = inportb((uint16) ntail->udata.intdata);
            if(debug)
            {
                messageBox("Got result from port");
            }
            break;
        }
        case outb:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t ntail = list_remove(&(env->istack), env->istack.size - 1);
            outportb((uint16) tail.udata.intdata, (uint8) ntail.udata.intdata);
            if(debug)
            {
                messageBox("Output byte to port");
            }
            break;
        }
        case outw:
        {
            element_t tail = list_remove(&(env->istack), env->istack.size - 1);
            element_t ntail = list_remove(&(env->istack), env->istack.size - 1);
            outportw((uint16) tail.udata.intdata, (uint8) ntail.udata.intdata);
            if(debug)
            {
                messageBox("Output word to port");
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

    if (tryCatchNests.size > 0)
    {
        int jmpLbl = etoi(list_remove(&(tryCatchNests), tryCatchNests.size - 1));
        element_t jmpIndex = hashmap_getVal(jmpPoints, itos10(jmpLbl));
        if(jmpIndex.ctype != INT)
        {
            messageBox("\x01 Destinated jump point has not been set");
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
    strcpy(vidmem, oldmem);
    return env->status;
}

