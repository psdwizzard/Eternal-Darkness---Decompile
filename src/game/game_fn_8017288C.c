extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80045A24(int, int);
extern const char lbl_8024FF00[];

int fn_8017288C(void* state)
{
    int first;
    int flags = 0;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    if ((int)lua_tonumber(state, 2) == 1) {
        flags |= 1;
    }
    fn_80045A24(first, flags);
    return 0;
}
