typedef struct Context {
    char* top;
    char pad04[12];
    char* stack;
} Context;

int lua_gettop(Context* context)
{
    return (context->top - context->stack) / 16;
}
