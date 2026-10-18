typedef int s32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C504;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027730(void*, s32, s32);

s32 fn_80017260(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    switch ((s32)lua_tonumber(script, 1)) {
    case 2:
        fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x2E, 0, 1), 0, 0);
        break;
    case 3:
        fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x2F, 0, 1), 0, 0);
        break;
    case 4:
        fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x30, 0, 1), 0, 0);
        break;
    case 5:
        fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x31, 0, 1), 0, 0);
        break;
    case 6:
        fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x32, 0, 1), 0, 0);
        break;
    }
    return 1;
}
