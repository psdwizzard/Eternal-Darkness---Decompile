extern void *memcpy(void *destination, const void *source, unsigned long size);
extern void lua_pushnumber(void *context, double value);
extern void lua_setglobal(void *context, const char *name);

int fn_80048344(void *context, const void *source, const char *name) {
    double value;

    memcpy(&value, source, sizeof(value));
    lua_pushnumber(context, value);
    lua_setglobal(context, name);
    return sizeof(value);
}
