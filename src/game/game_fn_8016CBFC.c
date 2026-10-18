extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80124750(void*, int, int, int, float, float, float, float, int);
extern const char lbl_8024FF00[];

int fn_8016CBFC(void* state)
{
    int second;
    int ninth;
    int seventh;
    int eighth;
    int first;
    float third;
    float fourth;
    float fifth;
    float sixth;

    if (lua_gettop(state) != 9) {
        luaO_verror(state, lbl_8024FF00, 9, lua_gettop(state));
        return 0;
    }
    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (float)lua_tonumber(state, 3);
    fourth = (float)lua_tonumber(state, 4);
    fifth = (float)lua_tonumber(state, 5);
    sixth = (float)lua_tonumber(state, 6);
    seventh = (int)lua_tonumber(state, 7);
    eighth = (int)lua_tonumber(state, 8);
    ninth = (int)lua_tonumber(state, 9);
    fn_80124750(fn_80201BC8(fn_80201814(first)), second, seventh, eighth,
                third, fourth, fifth, sixth, ninth | 8);
    return 0;
}
