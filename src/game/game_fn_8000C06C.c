typedef int s32;

extern const char lbl_8023BEF8[];
extern const char lbl_8023C11C[];
extern void* lbl_8064D5A8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern s32 fn_800DE298(void*);
extern void lua_pushnumber(void*, double);

s32 fn_8000C06C(void* script)
{
    void* handle = 0;
    s32 result = 0;
    s32 id;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    id = (s32)lua_tonumber(script, 1);
    if (id > 0) {
        handle = fn_80201814(id);
    }
    if (handle != 0 || id == 0) {
        result = fn_800DE298(handle);
    } else {
        luaO_verror(script, lbl_8023C11C, id, lbl_8064D5A8);
    }
    lua_pushnumber(script, result);
    return 1;
}
