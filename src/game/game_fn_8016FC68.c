extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8011FABC(void*, int, int);
extern const char lbl_8024FF00[];

int fn_8016FC68(void* state)
{
    int object_id;
    int clear_flags;
    int set_flags;
    void* object;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    clear_flags = (int)lua_tonumber(state, 2);
    set_flags = (int)lua_tonumber(state, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_8011FABC(fn_80201BC8(object), clear_flags, set_flags);
    }
    return 0;
}
