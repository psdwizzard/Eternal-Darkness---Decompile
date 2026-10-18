typedef struct Context {
    char pad00[0x5C];
    int limit;
} Context;

extern void luaC_checkGC(Context*, int);

void lua_setgcthreshold(Context* context, int value)
{
    if (value > 0x3FFFFF) {
        context->limit = -1;
    } else {
        context->limit = value << 10;
    }
    luaC_checkGC(context, value);
}
