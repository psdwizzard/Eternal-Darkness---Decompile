typedef unsigned char u8;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef int s32;

#pragma use_lmw_stmw on

typedef struct Vec {
    u32 x;
    u32 y;
    u32 z;
} Vec;

typedef struct Entry {
    u8 pad0[0x9E];
    u8 type;
    u8 state;
} Entry;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064D18C;
extern double lbl_8064DCF8;
extern void *fn_80201B9C();
extern int fn_80201B44();
extern void *fn_80201814();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern unsigned long long fn_8020123C();
extern void *fn_80201B8C();
extern int fn_80201EB8();
extern int fn_80201B5C(void*);
#define fn_80201B5C(a) fn_80201B5C((void*)(a))
extern int fn_80201B54();
extern int fn_80201B64(void*);
extern u32 fn_80178E94(Vec*, Vec*);
extern void* fn_80201BC0(void*);
extern void lua_pushnil(void*);
extern void lua_pushnumber(void*, double);

s32 fn_8000A0A0(void* script)
{
    Vec position;
    Vec entry_position_copy;
    Vec entry_position;
    register void* iterator;
    register s32 count;
    register s32 handle;
    register Entry* entry;
    register void* object;
    s32 message_result;

    iterator = fn_80201B9C();
    count = 0;
    handle = fn_80201B44();
    object = fn_80201814(handle);
    fn_80201E78(&position, object);
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    message_result = fn_8020123C(0x34, handle, handle, 0) & 0xFFFFFFFFULL;
    if (message_result != 0) {
        while (iterator != 0) {
            entry = fn_80201B8C(iterator);
            if (entry != 0 && lbl_8064D18C == fn_80201EB8(iterator) &&
                entry->type == 2 &&
                (entry->state == 3 ||
                 (u8)(entry->state - 4) <= 2 ||
                 entry->state == 7) &&
                fn_80201B5C(iterator) != 76) {
                message_result =
                    fn_8020123C(0x3B, handle, fn_80201B54(iterator), 0) &
                    0xFFFFFFFFULL;
                if (message_result == 0) {
                    fn_80201B64(iterator);
                }
                if (message_result != 0) {
                    fn_80201E78(&entry_position, iterator);
                    entry_position_copy = entry_position;
                    if (fn_80178E94(&position, &entry_position_copy) < 1000) {
                        count++;
                    }
                }
            }
            iterator = fn_80201BC0(iterator);
        }
        if (count != 0) {
            lua_pushnil(script);
        } else {
            lua_pushnumber(script, lbl_8064DCF8);
        }
    } else {
        lua_pushnil(script);
    }
    return 1;
}
