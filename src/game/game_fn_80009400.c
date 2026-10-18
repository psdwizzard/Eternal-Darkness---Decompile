typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8010F3DC(s32);

s32 fn_80009400(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    switch (value) {
    case 1:
        fn_8010F3DC(0x800);
        break;
    case 2:
        fn_8010F3DC(0x2000);
        break;
    case 3:
        fn_8010F3DC(0x1000);
        break;
    }
    return 0;
}
