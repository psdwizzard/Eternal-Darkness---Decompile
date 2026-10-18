typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80048708(void*);

s32 fn_8000BB98(void* script)
{
    void* handle;
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    handle = fn_80201814((s32)lua_tonumber(script, 1));
    object = handle != 0 ? fn_80201BC8(handle) : 0;
    if (handle != 0 && object != 0) {
        fn_80048708(object);
    }
    return 0;
}
