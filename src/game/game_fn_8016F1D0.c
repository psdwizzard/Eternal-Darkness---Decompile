extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801301B0(void*, int, int);
extern void fn_80130434(void*, int);
extern const char lbl_8024FF00[];

int fn_8016F1D0(void* state)
{
    void* object;
    int mode;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object = fn_80201BC8(fn_80201814((int)lua_tonumber(state, 1)));
    mode = (int)lua_tonumber(state, 2);
    if (mode != 0) {
        fn_801301B0(object, 0x20, 0);
    } else {
        fn_80130434(object, 1);
        fn_801301B0(object, 0, 0x20);
    }
    return 0;
}
