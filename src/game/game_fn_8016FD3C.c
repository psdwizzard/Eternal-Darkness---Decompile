extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80120AD0(void*, int, float, float, int, int);
extern const char lbl_8024FF00[];
extern float lbl_806506CC;

int fn_8016FD3C(void* state)
{
    int object_id;
    float value;
    int argument;
    int flags;
    void* object;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (float)lua_tonumber(state, 2);
    argument = (int)lua_tonumber(state, 3);
    flags = (int)lua_tonumber(state, 4);
    object = fn_80201814(object_id);
    if (object != 0) {
        object = fn_80201BC8(object);
        if ((unsigned short)flags != 0) {
            flags = (flags | 2) & 0xFFFF;
        }
        fn_80120AD0(object, 0, lbl_806506CC, value, argument, flags);
    }
    return 0;
}
