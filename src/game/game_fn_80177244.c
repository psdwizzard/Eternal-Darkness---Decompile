extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F6FFC(void*);
extern const char lbl_8024FF00[];
extern char lbl_8063CD18[];
extern char lbl_8063C6B8[];

int fn_80177244(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    fn_801F6FFC(lbl_8063CD18 + 0x198);
    fn_801F6FFC(lbl_8063C6B8 + 0x198);
    return 1;
}
