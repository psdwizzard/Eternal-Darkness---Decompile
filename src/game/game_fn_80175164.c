extern void fn_801FD240(void);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80175164(void* state)
{
    fn_801FD240();
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    asm {
        li r0, 12
        mtctr r0
    delay_loop:
        bdnz delay_loop
    }
    return 0;
}
