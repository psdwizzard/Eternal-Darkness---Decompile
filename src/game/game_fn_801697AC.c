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
    char pad00[8];
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
} Closure;

typedef struct Context {
    Value* top;
    char pad04[100];
    void* linehook;
} Context;

extern void fn_8016057C(Context*, int);
extern void fn_80160628(Context*, Value*, int);
extern void fn_80169740(Context*, Value*, int);

/*
 * Lua 4.0.1 luaV_execute reconstruction.  The entry/return and primitive
 * stack opcodes below establish the original VM state model; the remaining
 * opcode bodies still need to be recovered against the retail switch.
 */
Value* fn_801697AC(Context* context, Closure* closure, Value* base)
{
    Proto* proto = closure->proto;
    Value* top;
    Instruction* pc = proto->code;
    void** strings = proto->strings;
    void* linehook = context->linehook;
    Instruction instruction;

    ((Instruction***)(base[-1].value.pointer))[1] = &pc;
    fn_8016057C(context, proto->maxstacksize + 8);
    if (proto->is_vararg) {
        fn_80169740(context, base, proto->numparams);
    } else {
        fn_80160628(context, base, proto->numparams);
    }
    top = context->top;

    for (;;) {
        instruction = *pc++;
        if (linehook) {
            /* trace hook body is recovered in fn_80168AE8 */
        }
        switch (instruction & 0x3f) {
        case 0:
            context->top = top;
            return top;
        case 1:
            context->top = top;
            return base + (instruction >> 6);
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
        case 7:
            top->type = 3;
            top->value.pointer = strings[instruction >> 6];
            top++;
            break;
        default:
            context->top = top;
            return top;
        }
    }
}
