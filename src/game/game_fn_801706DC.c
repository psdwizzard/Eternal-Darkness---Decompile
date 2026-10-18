extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_801F8748(int, void*, int, int, int);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_801706DC(void* state)
{
    int first;
    int second;
    int third;
    int fourth;
    int result;
    int fifth;
    void* object;

    result = 0;
    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    first = fn_800F5C54(lua_tonumber(state, 1));
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);
    fourth = (int)lua_tonumber(state, 4);
    fifth = (int)lua_tonumber(state, 5);

    object = fn_80201814(second);
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            result = fn_801F8748(first, object, third, fourth, fifth);
        }
    }

    lua_pushnumber(state, result);
    return 1;
}
