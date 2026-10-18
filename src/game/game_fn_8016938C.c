typedef struct Value {
    int type;
    int pad04;
    union {
        double number;
        void* pointer;
    } value;
} Value;

typedef struct Context {
    int* stack;
} Context;

extern void luaD_checkstack(Context*, int);
extern int luaV_strcomp(void*, void*);
extern int call_binTM(Context*, void*, int);
extern void luaG_ordererror(Context*, void*);

int luaV_lessthan(Context* context, Value* left, Value* right, Value* output)
{
    if (left->type == 2 && right->type == 2) {
        return left->value.number < right->value.number;
    }
    if (left->type == 3 && right->type == 3) {
        return luaV_strcomp(left->value.pointer, right->value.pointer) < 0;
    }

    luaD_checkstack(context, 2);
    *output++ = *left;
    *output++ = *right;
    if (call_binTM(context, output, 11) == 0) {
        luaG_ordererror(context, output - 2);
    }
    context->stack = (int*)((char*)context->stack - 16);
    return *context->stack != 1;
}
