extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012C478(void*, int, int);
extern const char lbl_8024FF00[];
extern const char lbl_8025005C[];

int fn_8016F580(void* state)
{
    int object_id;
    void* object;
    void* runtime;
    int index;
    int enabled;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        index = (int)lua_tonumber(state, 2);
        enabled = (int)lua_tonumber(state, 3);
        fn_8012C478(runtime, index, enabled);
    } else {
        luaO_verror(state, lbl_8025005C, object_id);
    }
    return 0;
}
