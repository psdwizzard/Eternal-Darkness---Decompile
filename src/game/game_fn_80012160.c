typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_801DA058(s32);
extern void fn_800CD458(s32, s32, void*, s32, s32, s32, s32);

s32 fn_80012160(void* script)
{
    s32 handle;
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    handle = (s32)lua_tonumber(parser, 1);
    if (fn_80201814(handle) != 0) {
        fn_800CD458(handle, 0x11011, fn_801DA058(0x11011), 0, 0, 0, 0);
    }
    return 0;
}
