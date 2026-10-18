extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012B344(void*);
extern const char lbl_8024FF00[];

int fn_8016F128(void* state)
{
    void* handle;
    void* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    handle = fn_80201814((int)lua_tonumber(state, 1));
    object = handle != 0 ? fn_80201BC8(handle) : 0;
    if (handle != 0 && object != 0) {
        fn_8012B344(object);
    }
    return 0;
}
