extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AC350(signed char, int, int);
extern const char lbl_8024FF00[];
extern const char lbl_80250414[];

int fn_80172610(void* state)
{
    int value;
    signed char clamped;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        luaO_verror(state, lbl_80250414, value);
    }
    fn_801AC350(clamped, 0, 0);
    return 0;
}
