typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
#define FN_80128E30_RETURN void*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern void fn_8012880C(void*, s32, s32);

s32 fn_8000A4FC(void* script)
{
    void* object;
    void* result;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0) {
        result = fn_80201BC8(object);
    } else {
        result = 0;
    }
    if (result != 0) {
        fn_8012880C(fn_80128E30(result), 0, 0);
    }
    return 0;
}
