#pragma use_lmw_stmw on

typedef unsigned int Instruction;

typedef struct Value {
    int type;
    int pad04;
    union {
        double number;
        void* pointer;
    } value;
} Value;

typedef struct Proto {
    double* numbers;
    char pad04[4];
    void** strings;
    char pad0C[12];
    Instruction* code;
    char pad1C[4];
    short numparams;
    short is_vararg;
    short maxstacksize;
} Proto;

typedef struct Closure {
    Proto* proto;
    char pad04[12];
    Value upvalues[1];
} Closure;

typedef struct Context {
    Value* top;
    char pad04[100];
    void* linehook;
} Context;

extern void luaD_checkstack(Context*, int);
extern void luaD_adjusttop(Context*, Value*, int);
extern void adjust_varargs(Context*, Value*, int);
extern Value* luaV_getglobal(Context*, void*);
extern void traceexec(Context*, Value*, Value*, void*);
extern void luaD_call(Context*, Value*, int);

/*
 * Lua 4.0.1 luaV_execute reconstruction.  The entry/return and primitive
 * stack opcodes below establish the original VM state model; the remaining
 * opcode bodies still need to be recovered against the retail switch.
 */
Value* luaV_execute(Context* context, Closure* closure, Value* base)
{
    Proto* proto = closure->proto;
    Value* top;
    Instruction* pc = proto->code;
    void** strings = proto->strings;
    void* linehook = context->linehook;
    Instruction instruction;

    ((Instruction***)(base[-1].value.pointer))[1] = &pc;
    luaD_checkstack(context, proto->maxstacksize + 8);
    if (proto->is_vararg) {
        adjust_varargs(context, base, proto->numparams);
    } else {
        luaD_adjusttop(context, base, proto->numparams);
    }
    top = context->top;

    for (;;) {
        instruction = *pc++;
        if (linehook) {
            traceexec(context, base, top, linehook);
        }
        switch (instruction & 0x3f) {
        case 0:
            context->top = top;
            return top;
        case 1:
            context->top = top;
            return base + (instruction >> 6);
        case 2: {
            int results = (instruction >> 6) & 0x1ff;
            if (results == 0xff)
                results = -1;
            context->top = top;
            luaD_call(context, base + (instruction >> 15), results);
            top = context->top;
            break;
        }
        case 3:
            context->top = top;
            luaD_call(context, base + (instruction >> 15), -1);
            return base + ((instruction >> 6) & 0x1ff);
        case 4: {
            int count = instruction >> 6;
            do {
                top->type = 1;
                top++;
            } while (--count > 0);
            break;
        }
        case 5:
            top -= instruction >> 6;
            break;
        case 6:
            top->type = 2;
            top->value.number = (double)((int)(instruction >> 6) - 0x1ffffff);
            top++;
            break;
        case 7:
            top->type = 3;
            top->value.pointer = strings[instruction >> 6];
            top++;
            break;
        case 8:
            top->type = 2;
            top->value.number = proto->numbers[instruction >> 6];
            top++;
            break;
        case 9:
            top->type = 2;
            top->value.number = -proto->numbers[instruction >> 6];
            top++;
            break;
        case 10:
            *top++ = closure->upvalues[instruction >> 6];
            break;
        case 11:
            *top++ = base[instruction >> 6];
            break;
        case 12: {
            Value* value;
            context->top = top;
            value = luaV_getglobal(context, strings[instruction >> 6]);
            *top++ = *value;
            break;
        }
        default:
            context->top = top;
            return top;
        }
    }
}
