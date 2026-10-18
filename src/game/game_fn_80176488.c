extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201ADC(void);
extern void fn_80204EC8(void*, void*);
extern int fn_801E8328();
extern const char lbl_8024FF00[];

int fn_80176488(void* state)
{
    void* object;
    int object_id;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    if (object_id != 0) {
        object = fn_80201814(object_id);
        fn_80204EC8(fn_80201ADC(), object);
        fn_801E8328(2, object);
    }
    return 0;
}
