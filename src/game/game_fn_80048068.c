typedef struct Context Context;

extern void lua_getglobal(Context *context, const char *name);
extern double lua_tonumber(void *context, int index);
extern void lua_settop(Context *context, int count);
extern void *memcpy(void *destination, const void *source, unsigned long size);

int fn_80048068(Context *context, void *destination, const char *name)
{
    double value;

    lua_getglobal(context, name);
    value = lua_tonumber(context, 1);
    lua_settop(context, -2);
    memcpy(destination, &value, sizeof(value));
    return sizeof(value);
}
