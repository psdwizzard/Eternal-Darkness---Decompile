typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800E463C(void);
extern void fn_800E4648(void);
extern void fn_800E4674(void);

s32 fn_80013748(void* script)
{
    void* parser = script;

    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    if ((s32)lua_tonumber(parser, 1) != 0) {
        fn_800E463C();
        fn_800E4648();
    } else {
        fn_800E4674();
    }
    return 0;
}
