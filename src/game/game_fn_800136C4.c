typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_80204FDC(void*);

s32 fn_800136C4(void* script)
{
    void* parser = script;

    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    fn_80204FDC(fn_80201814((s32)lua_tonumber(parser, 1)));
    return 0;
}
