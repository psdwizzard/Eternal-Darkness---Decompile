extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern int lbl_8064D6E0;
extern int lbl_8064D6DC;

int fn_8016D92C(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    if (value != lbl_8064D6E0) {
        lbl_8064D6E0 = value;
        lbl_8064D6DC = 1;
    }
    return 0;
}
