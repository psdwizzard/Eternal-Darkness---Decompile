typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void *fn_80201814();

s32 fn_80014144(void* script)
{
    fn_80201814(fn_80201B44());
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    return 0;
}
