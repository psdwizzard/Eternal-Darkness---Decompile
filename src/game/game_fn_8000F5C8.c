typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern s32 fn_800359A0(void*, void*);
extern unsigned int fn_80036D5C(void*);
extern void fn_80036DA4(void*, u32);

s32 fn_8000F5C8(void* script)
{
    s32 first;
    s32 second;
    void* first_object;
    void* second_object;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    first_object = fn_80201814(first);
    second_object = fn_80201814(second);
    if (first_object != 0 && second_object != 0 &&
        fn_800359A0(first_object, second_object) != 0) {
        fn_80036DA4(first_object, fn_80036D5C(first_object) | 0x800);
    }
    return 0;
}
