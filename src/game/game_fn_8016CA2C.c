extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801247F8(void*, int, int, float);
extern const char lbl_8024FF00[];

int fn_8016CA2C(void* state)
{
    int second;
    int fourth;
    int first;
    float third;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }
    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (float)lua_tonumber(state, 3);
    fourth = (int)lua_tonumber(state, 4);
    fn_801247F8(fn_80201BC8(fn_80201814(first)), second, fourth, third);
    return 0;
}
