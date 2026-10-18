extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F0294(float, int);
extern const char lbl_8024FF00[];

int fn_80176870(void* state)
{
    float value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }
    value = (float)lua_tonumber(state, 1);
    fn_801F0294(value, (int)lua_tonumber(state, 2));
    return 0;
}
