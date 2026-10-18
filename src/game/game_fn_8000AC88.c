typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Entry {
    u8 pad0[8];
    struct Entry* child;
} Entry;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern void fn_8005F8D0(s32, Entry*, void*, Entry*, Entry*, s32, Vec3f*, u32,
                       s32);

s32 fn_8000AC88(void* script)
{
    s32 id;
    Entry* target;
    Entry* entry;
    u32 object_id;
    Vec3f position;
    Vec3s* source;
    void* info;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    id = (s32)lua_tonumber(script, 1);
    object_id = fn_800F5C54(lua_tonumber(script, 2));
    source = fn_80158ABC(fn_8015C4A4(object_id, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;

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
        fn_8005F8D0(id, entry, info, target, target->child, 0, &position,
                    object_id, 1);
    }
    return 0;
}
