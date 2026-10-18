extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void fn_801A7DEC(int);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern const char lbl_80250450[];

int fn_80172D04(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    if (value > 1 || value < 0) {
        luaO_verror(state, lbl_80250450, value);
    }
    fn_801A7DEC(value);
    return 0;
}
