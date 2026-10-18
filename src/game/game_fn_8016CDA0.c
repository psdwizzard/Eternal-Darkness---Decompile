extern int fn_80201B44();
extern void *fn_80201814();
extern int fn_80201EB8();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80200EAC(int, int, int, int, float);
extern const char lbl_8024FF00[];
extern const float lbl_806506B8;

int fn_8016CDA0(void* state)
{
    int first = fn_80201B44(state);
    int second = fn_80201EB8(fn_80201814(first));

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }
    fn_80200EAC(0x39, first, 0, second, lbl_806506B8);
    return 0;
}
