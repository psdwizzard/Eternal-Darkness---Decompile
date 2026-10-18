extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AD46C(unsigned char*, unsigned char*);
extern void fn_801AD4B4(int, int, int, int);
extern const char lbl_8024FF00[];

int fn_80171FBC(void* state)
{
    int value;
    unsigned char arg0;
    unsigned char arg1;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    fn_801AD46C(&arg0, &arg1);
    fn_801AD4B4(value, 0, 0, 0);
    return 0;
}
