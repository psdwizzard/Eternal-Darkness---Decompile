extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_802020B4(void*, int);
extern const char lbl_8024FF00[];

int fn_80176644(void* state)
{
    int object_id;
    int value;
    void* object;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_802020B4(object, value);
    }
    return 0;
}
