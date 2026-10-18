typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry {
    u8 pad0[8];
    struct Entry* child;
} Entry;

typedef struct Target {
    u8 pad0[0x8C];
    struct TargetData* data;
} Target;

typedef struct TargetData {
    u8 pad0[0x146];
    u16 value;
} TargetData;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void *fn_80201BC8();

s32 fn_8000AA8C(void* script)
{
    Target* target;
    Entry* entry;
    s32 first;
    s32 second;
    void* info;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    entry = fn_80201814(first);
    if (entry != 0) {
        target = (Target*)fn_80201B8C(entry);
    } else {
        target = 0;
    }
    if (entry != 0) {
        info = fn_80201BC8(entry);
    } else {
        info = 0;
    }
    if (info != 0 && target != 0 && target->data != 0) {
        target->data->value = (u16)second;
    }
    return 0;
}
