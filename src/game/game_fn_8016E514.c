extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801F700C(int, void*);
extern const char lbl_8024FF00[];

int fn_8016E514(void* state)
{
    int value;
    void* target;
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    value = (int)lua_tonumber(state, 1);
    fn_80201814(value);
    target = fn_80201BC8();
    fn_801F700C(2, target);
    return 1;
}
