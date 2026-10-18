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

extern void* luaS_newlstr(Context*, const char*, int);
extern void luaD_checkstack(Context*, int);

void lua_pushlstring(Context* context, const char* string, int length)
{
    ((Value*)context->current)->value = luaS_newlstr(context, string, length);
    ((Value*)context->current)->type = 3;
    if (context->current == context->end) {
        luaD_checkstack(context, 1);
    }
    context->current = (char*)context->current + 16;
}
