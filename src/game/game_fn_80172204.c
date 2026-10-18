extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AD404(unsigned char, unsigned char, int);
extern const char lbl_8024FF00[];
extern const char lbl_8025038C[];

int fn_80172204(void* state)
{
    int value;
    unsigned char clamped;
    int other;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    other = (int)lua_tonumber(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        luaO_verror(state, lbl_8025038C, value);
    }
    fn_801AD404(clamped, clamped, other);
    return 0;
}
