extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern int lbl_8064B814;

int fn_80176994(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    lbl_8064B814 = (int)lua_tonumber(state, 1);
    return 0;
}
