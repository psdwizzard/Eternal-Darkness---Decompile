extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801290D0(void*);
extern void fn_80128F74(void*, int);
extern void fn_801A5C30(int);
extern const char lbl_8024FF00[];
extern void* lbl_8064C4E4;

int fn_8016FE4C(void* state)
{
    int value;
    int flags;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    if (value == 0) {
        if (lbl_8064C4E4 != 0) {
            flags = fn_801290D0(lbl_8064C4E4);
            fn_80128F74(lbl_8064C4E4, flags | 4);
        }
    }
    fn_801A5C30(value);
    return 0;
}
