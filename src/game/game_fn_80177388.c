extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern char lbl_8063D378[];
extern char lbl_8063D400[];

int fn_80177388(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    *(int*)(lbl_8063D378 + 0x40) = 1;
    *(int*)(lbl_8063D400 + 0x40) = 1;
    return 1;
}
