typedef struct Value {
    int type;
    int pad04;
    union {
        double number;
        void* pointer;
    } value;
} Value;

typedef struct Context {
    Value* stack;
    int pad04;
    Value* end;
} Context;

extern void* luaH_new(Context*, int);
extern Value* luaH_setint(Context*, void*, int);
extern void* luaS_new(Context*, void*);
extern void luaH_setstrnum(Context*, void*, double, void*);
extern void luaD_checkstack(Context*, int);
extern int lbl_8064BBF8;

void luaV_pack(Context* context, Value* source)
{
    Value* current;
    int count;
    void* array;

    array = luaH_new(context, 0);
    current = source;
    count = 0;
    while (current < context->stack) {
        Value* destination = luaH_setint(context, array, count + 1);
        *destination = *current;
        ++current;
        ++count;
    }
    luaH_setstrnum(context, array, (double)count,
                luaS_new(context, &lbl_8064BBF8));
    context->stack = source;
    context->stack->type = 4;
    context->stack->value.pointer = array;
    if (context->stack == context->end) {
        luaD_checkstack(context, 1);
    }
    ++context->stack;
}
