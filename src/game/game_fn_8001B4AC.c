typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

extern const char lbl_8023BEF8[];
extern int fn_80201B44();
extern void* fn_80158598(int, int);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201C24();
extern void fn_801579E0(void*, s32, s32);
extern s32 fn_80158514(void*, s32);
extern void fn_800CC140(void*, s32, s32, s32, s32);
extern s32 fn_80157918(void*);
extern s32 fn_802006D4(s32, s32, s32, s32, s32);
extern s32 fn_80157AB8(void*);
extern void fn_80157B60(void*, s32);
extern void fn_80157B3C(void*, s32);
extern double fn_80200534(s32, s32, s32);
extern void fn_800DBF60(void*, double, void*, s32, s32);

s32 fn_8001B4AC(void* script)
{
    s32 first;
    s32 second;
    void* manager;
    void* list;
    void* second_object;
    void* first_state;
    void* second_state;
    s32 count;
    double value;

    manager = (void*)fn_80201B44();
    list = fn_80158598((s32)manager, 0);
    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    first = (u16)lua_tonumber(script, 1);
    second = (u16)lua_tonumber(script, 2);
    lua_tonumber(script, 3);

    fn_80201814(first);
    first_state = fn_80201C24();
    second_object = fn_80201814(second);
    second_state = fn_80201C24();

    fn_801579E0(first_state, 0, second);
    fn_801579E0(second_state, first, 0);

    if (fn_80158514(list, first) >= 0) {
        fn_800CC140(manager, first, 0, 2, 0);
        fn_800CC140(manager, first, 0, 2, 0);
    } else if (fn_80158514(list, second) >= 0) {
        fn_800CC140(manager, second, 0, 2, 0);
        fn_800CC140(manager, first, 0, 2, 0);
    }

    count = fn_80157918(first_state);
    if ((u8)count > 1) {
        fn_802006D4(second, second, -1, 75, 0);
        fn_80157B60(second_state, fn_80157AB8(first_state));
        fn_80157B3C(second_state, count);
        value = fn_80200534(first, -1, 75);
        fn_800DBF60((void*)fn_80201B44(), value, second_object, count, 0);
    }
    return 0;
}
