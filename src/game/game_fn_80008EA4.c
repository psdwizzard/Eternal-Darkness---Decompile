typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012B344(void*);
extern void fn_80129FD0(void*, s32, s32);

s32 fn_80008EA4(void* script)
{
    s32 actor;
    s32 value;
    void* object;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    actor = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);

    if (fn_80201814(actor) != 0) {
        object = fn_80201BC8();
    } else {
        object = 0;
    }

    if (object != 0) {
        fn_8012B344(object);
        fn_80129FD0(object, value << 17, 0);
    }

    return 0;
}
