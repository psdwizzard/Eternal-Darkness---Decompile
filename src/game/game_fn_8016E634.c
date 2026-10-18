typedef unsigned short u16;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801FA454(int, u16);
extern const char lbl_8024FF00[];

int fn_8016E634(void* state)
{
    int first;
    u16 second;
    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }
    first = (int)lua_tonumber(state, 1);
    second = (u16)(int)lua_tonumber(state, 2);
    fn_801FA454(first, second);
    return 0;
}
