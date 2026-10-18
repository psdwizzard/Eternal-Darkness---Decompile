typedef int s32;
typedef unsigned char u8;

typedef struct Entry {
    u8 pad0[8];
    struct Entry* child;
} Entry;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern void fn_8005F8D0(s32, Entry*, void*, Entry*, Entry*, s32, s32, s32,
                       s32);

s32 fn_8000AB88(void* script)
{
    Entry* target;
    Entry* entry;
    s32 id;
    void* info;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    id = (s32)lua_tonumber(script, 1);
    entry = fn_80201814(id);
    if (entry != 0) {
        target = fn_80201B8C(entry);
    } else {
        target = 0;
    }
    if (entry != 0) {
        info = fn_80201BC8(entry);
    } else {
        info = 0;
    }
    if (info != 0 && target != 0) {
        fn_8005F8D0(id, entry, info, target, target->child, 0, 0, 0, 1);
    }
    return 0;
}
