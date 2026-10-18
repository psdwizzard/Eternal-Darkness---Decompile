typedef int s32;
typedef unsigned char u8;

typedef struct Entry {
    u8 pad0[8];
    struct Entry* child;
} Entry;

typedef struct Target {
    u8 pad0[0x89];
    u8 flags;
} Target;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000A9A4(void* script)
{
    s32 first;
    s32 second;
    Entry* entry;
    Target* target;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    entry = fn_80201814(first);
    if (entry != 0) {
        entry = fn_80201B8C(entry);
    } else {
        entry = 0;
    }
    if (entry != 0) {
        target = (Target*)entry->child;
        if (target != 0) {
            if (second != 0) {
                target->flags |= 2;
            } else {
                target->flags &= ~2;
            }
        }
    }
    return 0;
}
