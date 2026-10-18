typedef unsigned short u16;
typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern u16 fn_800289A4(void*, s32, s32);
extern void fn_801FA198(void*, void*, s32, s32, s32, s32, s32, s32, s32);
extern char lbl_8023BEF8[];
extern char lbl_8063CD18[];

s32 fn_8001CFB8(void* script)
{
    s32 second;
    s32 fourth;
    s32 fifth;
    s32 third;
    void* first;
    s32 sixth;

    if (lua_gettop(script) != 6) {
        luaO_verror(script, lbl_8023BEF8, 6, lua_gettop(script));
        return 0;
    }

    first = (void *)fn_800F5C54(lua_tonumber(script, 1));
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);

    if (fn_800289A4(first, fourth, sixth) != 0) {
        fourth = 0;
    }

    fn_801FA198(first, lbl_8063CD18 + 0x110, second, third, fourth, 0, 0, fifth, 0);
    return 0;
}
