typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern u32 fn_8011FAEC(void*);
extern void fn_8011FADC(void*, u32);
extern void fn_80048708(void*);

s32 fn_8000B20C(void* script)
{
    void* object;
    void* info;
    u32 flags;
    u32 first_flags;
    s32 first_flag;
    s32 second_flag;
    s32 third_flag;
    s32 object_id;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    first_flag = (s32)lua_tonumber(script, 2);
    second_flag = (s32)lua_tonumber(script, 3);
    third_flag = (s32)lua_tonumber(script, 4);
    object = fn_80201814(object_id);
    info = object != 0 ? fn_80201BC8(object) : 0;

    if (object != 0 && info != 0) {
        first_flags = fn_8011FAEC(info);
        flags = first_flags | 2;
        if (first_flag != 0) {
            flags = first_flags & ~2;
        }
        first_flags = flags & ~0x80;
        if (second_flag != 0) {
            first_flags = flags | 0x80;
        }
        fn_8011FADC(
            info,
            third_flag != 0 ? first_flags | 0x40 : first_flags & ~0x40);
        if (second_flag != 0 || third_flag != 0) {
            fn_80048708(info);
        }
    }
    return 0;
}
