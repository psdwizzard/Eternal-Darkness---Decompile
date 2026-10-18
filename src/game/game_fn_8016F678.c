extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern unsigned int fn_8011FA8C(void*, int, int);
extern const char lbl_8024FF00[];
extern const char lbl_8025005C[];

int fn_8016F678(void* state)
{
    int object_id;
    void* object;
    void* runtime;
    int clear_flags = 0;
    int set_flags = 0;
    int enabled;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        enabled = (int)lua_tonumber(state, 2);
        if (enabled != 0) {
            set_flags = 4;
        }
        if (enabled == 0) {
            clear_flags = 4;
        }
        fn_8011FA8C(runtime, clear_flags, set_flags);
    } else {
        luaO_verror(state, lbl_8025005C, object_id);
    }
    return 0;
}
