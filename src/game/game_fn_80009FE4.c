typedef unsigned long long u64;
typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];
extern double lbl_8064DCF8;
extern int fn_80201B44();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern unsigned long long fn_8020123C();
extern void lua_pushnumber(void*, double);
extern void *fn_80201814();
extern void lua_pushnil(void*);

s32 fn_80009FE4(void* script)
{
    register s32 handle;
    u32 message_result;

    handle = fn_80201B44();
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }
    message_result = fn_8020123C(0x34, handle, handle, 0) & 0xFFFFFFFFULL;
    if (message_result != 0) {
        lua_pushnumber(script, lbl_8064DCF8);
    } else {
        fn_80201814(handle);
        lua_pushnil(script);
    }
    return 1;
}
