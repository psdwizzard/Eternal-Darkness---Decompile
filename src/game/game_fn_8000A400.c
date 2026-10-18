typedef unsigned char u8;
typedef int s32;

typedef struct Entry {
    u8 pad0[0x9E];
    u8 type;
    u8 state;
} Entry;

extern s32 lbl_8064D18C;
extern const char lbl_8023BEF8[];
extern void *fn_80201B9C();
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201B8C();
extern int fn_80201EB8();
extern void* fn_80201BC0(void*);
extern void fn_802020B4(void*, int);

s32 fn_8000A400(void* script)
{
    void* iterator;
    Entry* entry;

    iterator = fn_80201B9C();
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    script = (void*)(s32)lua_tonumber(script, 1);
    while (iterator != 0) {
        entry = fn_80201B8C(iterator);
        if (entry != 0 && lbl_8064D18C == fn_80201EB8(iterator) &&
            entry->type == 2 && entry->state == 6) {
            fn_802020B4(iterator, (s32)script);
        }
        iterator = fn_80201BC0(iterator);
    }
    return 1;
}
