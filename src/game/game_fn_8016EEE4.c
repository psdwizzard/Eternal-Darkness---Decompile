extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8012A1BC(void*, int);
extern void fn_80128A84(void*, unsigned short, unsigned int);
extern const char lbl_8024FF00[];

int fn_8016EEE4(void* state)
{
    void* callback;
    void* object;
    int object_id;
    int value;
    int result;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    callback = lua_touserdata(state, 2);
    value = (int)lua_tonumber(state, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        object = fn_80201BC8(object);
        result = fn_8012A1BC(object, value);
        fn_80128A84(callback, 0, result);
    }
    return 0;
}
