typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void* fn_80201B3C();
extern void* fn_80201C24();
extern void* fn_80049220(void*, s32);
extern s32 fn_80049304(void*, void*);
extern void* fn_802053B0(void*, void*);
extern int fn_80201B54();

s32 fn_8000DAF4(void* script)
{
    void* context;
    void* object;
    void* value;
    void* handle;

    context = fn_80201B3C();
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    value = fn_80049220(context, 1);
    fn_80049304(context, value);
    handle = fn_80201C24();
    object = fn_802053B0(context, handle);
    lua_pushnumber(script, (double)(object != 0 ? fn_80201B54(object) : 0));
    return 1;
}
