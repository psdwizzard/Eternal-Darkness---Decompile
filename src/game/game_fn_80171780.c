extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801A9984(int, unsigned char);
extern const char lbl_8024FF00[];
extern const char lbl_80250284[];

int fn_80171780(void* state)
{
    unsigned char clamped;
    int handle;
    int value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    handle = fn_800F5C54(lua_tonumber(state, 1));
    value = (int)lua_tonumber(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        luaO_verror(state, lbl_80250284, value, 0x7F);
    }
    fn_801A9984(handle, clamped);
    return 0;
}
