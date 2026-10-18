extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AD4B4(int, int, int, unsigned short);
extern const char lbl_8024FF00[];
extern unsigned int lbl_8064D1BC;

int fn_80172058(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    fn_801AD4B4(value, 0, 0, (unsigned short)lbl_8064D1BC);
    return 0;
}
