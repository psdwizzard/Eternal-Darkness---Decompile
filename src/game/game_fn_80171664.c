extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_801A98F4(unsigned short, unsigned char);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];
extern const char lbl_80250284[];

int fn_80171664(void* state)
{
    int id;
    int value;
    unsigned char clamped;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        luaO_verror(state, lbl_80250284, value, 0x7F);
    }
    lua_pushnumber(state, fn_801A98F4((unsigned short)id, clamped));
    return 1;
}
