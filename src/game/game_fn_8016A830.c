typedef struct Context {
    void* current;
    int pad04;
    void* end;
} Context;

typedef struct Value {
    int type;
    int pad04;
    double value;
} Value;

extern void luaD_checkstack(Context*, int);

void lua_pushnumber(Context* context, double value)
{
    ((Value*)context->current)->value = value;
    ((Value*)context->current)->type = 2;
    if (context->current == context->end) {
        luaD_checkstack(context, 1);
    }
    context->current = (char*)context->current + 16;
}
