extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F348C(void*, int);
extern const char lbl_8024FF00[];

int fn_80174DB8(void* state)
{
    struct Bytes {
        unsigned char data[4];
    } converted, value;
    int parameter;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    converted.data[0] = lua_tonumber(state, 1);
    converted.data[1] = lua_tonumber(state, 2);
    converted.data[2] = lua_tonumber(state, 3);
    converted.data[3] = lua_tonumber(state, 4);
    parameter = lua_tonumber(state, 5);
    value = converted;
    fn_801F348C(&value, parameter);
    return 0;
}
