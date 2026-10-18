typedef unsigned short u16;
typedef signed short s16;
typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern unsigned long long fn_8020123C();
extern void* fn_8011F130(void*);
extern void* fn_801A717C(void*);
extern void fn_801A7228(void*);
extern void fn_801A7470(void*, s32);
extern void fn_801A74A0(void*, s32);
extern void fn_801A74A8(void*, s32);
extern void fn_801A7518(void*, s16);
extern void fn_801A7538(void*, u16);
extern void fn_801A764C(void*, void*);

s32 fn_8000E4CC(void* script)
{
    void* object;
    s32 flags;
    s32 mode;
    s32 object_id;
    s32 source_id;
    s32 value;
    void* event;
    void* source;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    source_id = (s32)lua_tonumber(script, 2);
    value = (s32)lua_tonumber(script, 3);
    flags = (s32)lua_tonumber(script, 4);
    mode = (s32)lua_tonumber(script, 5);

    object = fn_80201814(object_id);
    if (object != 0) {
        event = fn_801A717C(object);
        fn_801A74A0(event, source_id);
        fn_801A74A8(event, object_id);
        fn_801A7538(event, (u16)(1 << flags));
        fn_801A7470(event, mode);
        fn_801A7518(event, (s16)value);

        if (source_id > 0 &&
            (source = fn_80201814(source_id)) != 0) {
            fn_801A764C(event, fn_8011F130(fn_80201BC8(source)));
        } else {
            fn_801A764C(event, fn_8011F130(fn_80201BC8(object)));
        }

        fn_8020123C(0x27, source_id, object_id, event);
        fn_801A7228(event);
    }
    return 0;
}
