extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_802019EC(int, void*);
extern unsigned long long fn_8020123C();
extern const char lbl_8024FF00[];
extern void* lbl_8064D18C;

int fn_80171418(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = lua_tonumber(state, 1);
    if (value != 0) {
        void* object = fn_802019EC(value, lbl_8064D18C);
        fn_8020123C(0x12, 0, object, 0);
    }
    return 0;
}
