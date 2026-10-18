extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801E79A0(void*, int);
extern void fn_801E7974(void*, int);
extern void* lbl_8064C4E0;
extern const char lbl_8024FF00[];
extern const char lbl_802501CC[];

int fn_80170D04(void* state)
{
    int handle;
    int mode;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    handle = fn_800F5C54(lua_tonumber(state, 1));
    mode = lua_tonumber(state, 2);
    if (mode != 0 && mode != 1) {
        luaO_verror(state, lbl_802501CC, mode);
    }

    if (mode == 0) {
        fn_801E79A0(lbl_8064C4E0, handle);
    } else {
        fn_801E7974(lbl_8064C4E0, handle);
    }
    return 0;
}
