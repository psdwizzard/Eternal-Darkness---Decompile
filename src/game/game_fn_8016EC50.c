extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_801294DC(void*, int, int, int);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];

int fn_8016EC50(void* state)
{
    int value;
    int converted;
    int object_id;
    int mode;
    void* object;
    void* result;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    converted = fn_800F5C54(lua_tonumber(state, 3));
    mode = (int)lua_tonumber(state, 4);
    object = fn_80201814(object_id);
    object = object != 0 ? fn_80201BC8(object) : 0;
    result = object != 0 ? fn_801294DC(object, value, converted, mode) : 0;
    lua_pushusertag(state, result, 0);
    return 1;
}
