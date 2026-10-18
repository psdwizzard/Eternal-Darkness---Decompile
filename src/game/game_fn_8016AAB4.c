typedef struct Context {
    void* current;
    int pad04;
    void* end;
} Context;

typedef struct Value {
    int type;
    int pad04;
    void* value;
} Value;

extern void* luaH_new(Context*, int);
extern void luaD_checkstack(Context*, int);

void lua_newtable(Context* context)
{
    ((Value*)context->current)->value = luaH_new(context, 0);
    ((Value*)context->current)->type = 4;
    if (context->current == context->end) {
        luaD_checkstack(context, 1);
    }
    context->current = (char*)context->current + 16;
}
