typedef struct Pair {
    const char* name;
    void* value;
} Pair;

typedef struct Context Context;

extern void lua_pushcclosure(Context*, void*, int);
extern void lua_setglobal(Context*, const char*);

void luaL_openlib(Context* context, Pair* pairs, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        lua_pushcclosure(context, pairs[i].value, 0);
        lua_setglobal(context, pairs[i].name);
    }
}
