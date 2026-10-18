typedef struct Context {
    void* current;
} Context;

extern void* luaS_new(Context*, const char*);
extern void luaV_setglobal(Context*, void*);

void lua_setglobal(Context* context, const char* name)
{
    void* current = context->current;
    luaV_setglobal(context, luaS_new(context, name));
    context->current = (char*)current - 16;
}
