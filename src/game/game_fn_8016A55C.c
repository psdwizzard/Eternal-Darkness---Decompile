typedef struct Value {
    int type;
    int pad04;
    double number;
} Value;

typedef struct Context {
    Value* top;
    char pad04[12];
    Value* stack;
} Context;

Value* luaA_indexAcceptable(Context* context, int index)
{
    Value* value;
    if (index >= 0) {
        index--;
        value = context->stack + index;
        if (value >= context->top)
            return 0;
        return value;
    }
    return context->top + index;
}
