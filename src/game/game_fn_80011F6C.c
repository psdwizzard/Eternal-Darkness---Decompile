typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_80201B3C();
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();

s32 fn_80011F6C(void* script)
{
    void* entry;
    void* parser;

    parser = script;
    entry = fn_80201B3C();
    if (lua_gettop(parser) != 0) {
        luaO_verror(parser, lbl_8023BEF8, 0, lua_gettop(parser));
        return 0;
    }

    if (entry != 0) {
        fn_80201BC8(entry);
        fn_80201B54(entry);
        fn_80201B8C(entry);
    }
    return 0;
}
