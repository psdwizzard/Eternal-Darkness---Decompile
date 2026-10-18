typedef struct Context {
    char* top;
    char pad04[12];
    char* stack;
} Context;

extern void luaD_adjusttop(Context*, char*, int);

void lua_settop(Context* context, int count)
{
    if (count >= 0) {
        luaD_adjusttop(context, context->stack, count);
    } else {
        context->top = context->top + 16 + (count << 4);
    }
}
