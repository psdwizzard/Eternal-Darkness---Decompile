extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AC5E4(int, unsigned char, unsigned char, int, signed char, int, int);
extern const char lbl_8024FF00[];

int fn_80171D6C(void* state)
{
    struct {
        const char* strings;
    } args;
    int arg1;
    int arg2;
    unsigned char clamped2;
    int arg3;
    int arg4;
    unsigned char clamped1;
    signed char clamped4;

    args.strings = lbl_8024FF00;
    if (lua_gettop(state) != 4) {
        luaO_verror(state, args.strings, 4, lua_gettop(state));
        return 0;
    }
    arg1 = (int)lua_tonumber(state, 1);
    arg2 = (int)lua_tonumber(state, 2);
    arg3 = (int)lua_tonumber(state, 3);
    arg4 = (int)lua_tonumber(state, 4);
    clamped2 = (arg2 > 0 ? arg2 : 0) > 0x7F ? 0x7F : (arg2 > 0 ? arg2 : 0);
    if (arg2 != clamped2)
        luaO_verror(state, args.strings + 0x3A8, arg2, 0x7F);
    clamped4 = (arg4 > 0 ? arg4 : 0) > 0x7F ? 0x7F : (arg4 > 0 ? arg4 : 0);
    if (arg4 != clamped4)
        luaO_verror(state, args.strings + 0x40C, arg4);
    clamped1 = (arg1 > 0 ? arg1 : 0) > 0xFF ? 0xFF : (arg1 > 0 ? arg1 : 0);
    if (arg1 != clamped1)
        luaO_verror(state, args.strings + 0x434, arg4);
    fn_801AC5E4(0, clamped1, clamped2, arg3, clamped4, 0, 0);
    return 0;
}
