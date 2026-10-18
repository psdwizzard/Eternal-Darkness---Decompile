typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E0;
extern s32 lbl_8064C5D8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801119DC(s32, u32);
extern int fn_801E79FC(void*, int);
extern void fn_801E7974(void*, int);
extern s32 fn_80111C48(void);
extern s32 fn_801118E8(void);

s32 fn_8001299C(void* script)
{
    s32 first;
    u32 second;
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 2) {
        luaO_verror(parser, lbl_8023BEF8, 2, lua_gettop(parser));
        return 0;
    }

    first = (s32)lua_tonumber(parser, 1);
    second = fn_800F5C54(lua_tonumber(parser, 2));
    fn_801119DC(first, second);
    if (fn_801E79FC(lbl_8064C4E0, 0x3C) == 0) {
        fn_801E7974(lbl_8064C4E0, 0x3D);
        fn_80111C48();
        if (fn_801118E8() != 0) {
            lbl_8064C5D8 = 1;
        }
    } else if (fn_80111C48() != 0) {
        lbl_8064C5D8 = 1;
    }
    return 0;
}
