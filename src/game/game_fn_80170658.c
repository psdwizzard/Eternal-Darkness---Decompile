extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F7034(void*, int);
extern const char lbl_8024FF00[];
extern unsigned char lbl_8063CD18[];

int fn_80170658(void* state)
{
    unsigned char* target;

    target = lbl_8063CD18 + 0x110;
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    fn_801F7034(target, 0);
    return 0;
}
