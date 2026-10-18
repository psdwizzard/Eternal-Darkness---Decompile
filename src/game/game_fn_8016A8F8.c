typedef unsigned long size_t;

extern size_t strlen(const char*);
extern void lua_pushnil(void*);
extern void lua_pushlstring(void*, const char*, int);

void lua_pushstring(void* context, const char* string)
{
    if (string == 0) {
        lua_pushnil(context);
    } else {
        lua_pushlstring(context, string, strlen(string));
    }
}
