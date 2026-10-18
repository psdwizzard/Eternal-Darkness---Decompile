extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F3528(void*);
extern const char lbl_8024FF00[];

int fn_80174CD4(void* state)
{
    struct Bytes {
        unsigned char data[4];
    } converted, value;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    converted.data[0] = lua_tonumber(state, 1);
    converted.data[1] = lua_tonumber(state, 2);
    converted.data[2] = lua_tonumber(state, 3);
    converted.data[3] = lua_tonumber(state, 4);
    value = converted;
    fn_801F3528(&value);
    return 0;
}
