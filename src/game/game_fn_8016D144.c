extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void fn_80201F80(void*, int, int);
extern const char lbl_8024FF00[];

int fn_8016D144(void* state)
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
        fn_80201F80(object, value, 0xFF800);
    }
    return 0;
}
