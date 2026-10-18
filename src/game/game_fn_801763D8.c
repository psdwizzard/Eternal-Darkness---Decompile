extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
typedef struct Object Object;
extern void *fn_80201C24();
extern void fn_80157A28(Object*, unsigned short);
extern const char lbl_8024FF00[];

int fn_801763D8(void* state)
{
    int object_id;
    int value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    if (fn_80201814(object_id) != 0) {
        fn_80157A28(fn_80201C24(), (unsigned short)value);
    }
    return 0;
}
