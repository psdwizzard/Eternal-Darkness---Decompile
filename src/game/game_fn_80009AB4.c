typedef signed short s16;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef int s32;

#pragma use_lmw_stmw on

extern const char lbl_8023BEF8[];
extern s32 fn_800DE3F8(void);
extern s32 fn_800DE354(void);
extern void *fn_80201814();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern unsigned long long fn_8020123C();
extern int fn_80038308(void *, int, short *);
extern int fn_80038464(void*, int, s16*);
extern void lua_pushnumber(void*, double);

s32 fn_80009AB4(void* script)
{
    s16 first;
    s16 second;
    register void* object;
    register s32 result;
    register s32 handle;
    u32 message_result;

    first = 0;
    second = 0;
    result = 0;
    handle = fn_800DE3F8();
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    object = fn_80201814(fn_800DE354());
    if (handle != 0) {
        message_result =
            fn_8020123C(0x3B, fn_80201B44(), handle, 0) & 0xFFFFFFFFULL;
        if (message_result != 0 && object != 0) {
            fn_80038308(object, 0, &first);
            fn_80038464(object, 0, &second);
            if (first < second) {
                result = 1;
            }
        }
    }

    lua_pushnumber(script, (double)result);
    return 1;
}
