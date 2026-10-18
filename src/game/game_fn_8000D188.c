typedef int s32;

extern const char lbl_8023BEF8[];
extern char lbl_80302060[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);
s32 fn_8000D188(void* script)
{
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    fn_80201E78(lbl_80302060, object);
    return 0;
}
