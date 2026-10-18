typedef unsigned char u8;
typedef int s32;

typedef struct ObjectInfo {
    void* object;
} ObjectInfo;

typedef struct Object {
    char pad0[0x5E];
    u8 value;
} Object;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_80201B3C();
extern void *fn_80201B8C();

s32 fn_8000ED44(void* script)
{
    s32 value = 0;
    void* object;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    object = fn_80201B3C();
    if (object != 0) {
        value = ((Object*)((ObjectInfo*)fn_80201B8C(object))->object)->value;
    }
    lua_pushnumber(script, value);
    return 1;
}
