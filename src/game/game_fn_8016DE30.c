extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801F6370(void*, int);
extern const char lbl_8024FF00[];

int fn_8016DE30(void* state)
{
    void* object;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object = (void *)fn_800F5C54(lua_tonumber(state, 1));
    fn_801F6370(object, (int)lua_tonumber(state, 2));
    return 0;
}
