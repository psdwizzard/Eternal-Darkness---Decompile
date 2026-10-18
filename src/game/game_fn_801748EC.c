typedef signed short s16;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8016ADF0(s16, int, int);
extern int lbl_8064D1BC;
extern const char lbl_80250164[];

int fn_801748EC(void* state)
{
    int count;
    s16 id;

    count = lua_gettop(state);
    id = lbl_8064D1BC;
    switch (count) {
    case 2:
        id = lua_tonumber(state, 2);
    case 1:
        lua_tonumber(state, 1);
        break;
    default:
        luaO_verror(state, lbl_80250164, count);
        break;
    }

    fn_8016ADF0(id, -1, lua_tonumber(state, 1));
    return 0;
}
