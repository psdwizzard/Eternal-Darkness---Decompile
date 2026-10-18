typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];
extern float lbl_8064DCF0;
extern float lbl_8064DCF4;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern unsigned int fn_80036D5C(void*);
extern void fn_80036DA4(void*, u32);
extern s32 fn_801261F4(void*);
extern void fn_80120AD0(void*, s32, s32, s32, float, float);

s32 fn_80009BE8(void* script)
{
    register void* object;
    register void* target;
    register s32 value;
    register u32 flags;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    lua_tonumber(script, 2);
    object = fn_80201814(value);
    if (object != 0) {
        target = fn_80201BC8(object);
    } else {
        target = 0;
    }
    if (object != 0 && target != 0) {
        flags = fn_80036D5C(object);
        fn_80036DA4(object, flags | 0x01000000);
        fn_801261F4(target);
        fn_80120AD0(target, 0, 100, 522, lbl_8064DCF0, lbl_8064DCF4);
    }
    return 0;
}
