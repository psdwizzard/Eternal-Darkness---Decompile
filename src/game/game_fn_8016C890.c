extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern unsigned long long fn_8020123C();
extern const char lbl_8024FF00[];

int fn_8016C890(void* state)
{
    void* object;
    int other;
    int value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }
    value = (int)lua_tonumber(state, 1);
    other = (int)lua_tonumber(state, 2);
    object = fn_80201814(value);
    if (object != 0) {
        fn_80201D34(object, other);
        fn_80201D1C(object, 1);
        fn_8020123C(0x3B, value, value, 0);
    }
    return 0;
}
