extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80124664(void*, int, int, float);
extern const char lbl_8024FF00[];

int fn_8016CB24(void* state)
{
    int second;
    int first;
    float third;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }
    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (float)lua_tonumber(state, 3);
    fn_80124664(fn_80201BC8(fn_80201814(first)), second, 8, third);
    return 0;
}
