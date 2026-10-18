extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern int fn_80201B44();
extern int fn_802019EC(int, int);
extern void *fn_80201814();
extern int fn_80201C2C(void*);
extern int fn_80201948(int, int);
extern void *fn_80201B9C();
extern int fn_80201B5C(void*);
extern int fn_80201B54();
extern void* fn_80201BC0(void*);
extern void lua_pushnil(void*);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];
extern int lbl_8064D18C;

int fn_8016D2B8(void* state)
{
    int mode;
    int argument;
    int result = 0;
    int resolved;
    void* node;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }
    mode = (int)lua_tonumber(state, 1);
    if (mode == 6) {
        node = lua_touserdata(state, 2);
    }
    if (mode != 6) {
        argument = (int)lua_tonumber(state, 2);
    }
    switch (mode) {
    case 1:
        result = fn_80201B44();
        break;
    case 2:
        result = fn_802019EC(argument, lbl_8064D18C);
        break;
    case 4:
        result = fn_802019EC(argument, -1);
        break;
    case 5:
        resolved = fn_80201C2C(fn_80201814(fn_80201B44()));
        result = fn_80201948(argument, resolved);
        break;
    case 3:
        node = fn_80201B9C();
        while (node != 0) {
            if (argument == fn_80201B5C(node)) {
                result = fn_80201B54(node);
            }
            node = fn_80201BC0(node);
        }
        break;
    case 6:
        result = fn_80201B54(node);
        break;
    }
    if (result <= 0) {
        lua_pushnil(state);
    } else {
        lua_pushnumber(state, (double)result);
    }
    return 1;
}
