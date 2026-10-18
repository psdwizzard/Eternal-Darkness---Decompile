typedef unsigned char u8;
typedef int s32;

typedef struct ObjectInfo {
    char pad0[0x9F];
    u8 value;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000EBD4(void* script)
{
    s32 value = -1;
    s32 i;
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0) {
        value = ((ObjectInfo*)fn_80201B8C(object))->value;
    }
    for (i = 0; i < 1; i++) {
        lua_pushnumber(script, value);
    }
    return 1;
}
