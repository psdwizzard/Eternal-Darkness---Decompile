extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F898C(void*, int);
extern const char lbl_8024FF00[];
extern char lbl_8063CD18[];

int fn_8016E5A8(void* state)
{
    int value;
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    value = (int)lua_tonumber(state, 1);
    fn_801F898C(lbl_8063CD18 + 0x110, value);
    return 0;
}
