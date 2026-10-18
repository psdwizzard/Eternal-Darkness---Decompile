typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_80201EB8();
extern void lua_pushnumber(void*, double);

s32 fn_8000B36C(void* script)
{
    void* object;
    s32 value = -1;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0) {
        fn_80201BC8(object);
    }
    if (object != 0) {
        value = fn_80201EB8(object);
    }
    lua_pushnumber(script, value);
    return 1;
}
