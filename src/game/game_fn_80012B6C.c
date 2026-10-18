typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C500;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern s32 fn_80047180(void);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027730(void*, s32, s32);
extern int fn_801A98F4(int, int);

s32 fn_80012B6C(void* script)
{
    s32 first;
    s32 second;
    s32 blocked;
    void* parser;

    blocked = 0;
    parser = script;
    if (lua_gettop(parser) != 4 && lua_gettop(parser) != 3) {
        luaO_verror(parser, lbl_8023BEF8, 3, lua_gettop(parser));
        return 0;
    }

    first = fn_800F5C54(lua_tonumber(parser, 1));
    second = fn_800F5C54(lua_tonumber(parser, 2));
    if (fn_80047180() == 0) {
        switch (first) {
        case 0x80:
            switch (second) {
            case 0:
                blocked = 1;
                break;
            }
            break;
        case 0x35:
            switch (second) {
            case 0:
                blocked = 1;
                break;
            }
            break;
        }
    }

    if (blocked == 0) {
        fn_80027730(
            fn_801E6CA0(lbl_8064C500, first, second, 0, 1),
            (s32)lua_tonumber(parser, 3),
            0);
    } else {
        fn_801A98F4(0x67, 0x64);
    }
    return 0;
}
