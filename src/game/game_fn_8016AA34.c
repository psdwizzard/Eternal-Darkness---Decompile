typedef struct Context {
    void* current;
    int pad04;
    void* end;
} Context;

typedef struct Value {
    double first;
    double second;
} Value;

extern void* luaS_new(Context*, const char*);
extern Value* luaV_getglobal(Context*, void*);
extern void luaD_checkstack(Context*, int);

void lua_getglobal(Context* context, const char* name)
{
    Value* current = (Value*)context->current;
    *current = *luaV_getglobal(context, luaS_new(context, name));
    context->current = current;
    if (context->current == context->end) {
        luaD_checkstack(context, 1);
    }
    context->current = (char*)context->current + 16;
}
