typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef union {
    u8 bytes[144];
    struct {
        u8 prefix[40];
        u8 body[104];
    } layout;
} SpawnDescriptor;

typedef struct {
    u8 bytes[172];
    u8 stack_padding[2];
} SpawnInfo;

typedef struct {
    s32 first;
    s32 second;
} ValuePair;

extern const char lbl_8023CBC8[];
extern s32 lbl_8064D18C;
extern const f32 lbl_8064DCF4;
extern const f32 lbl_8064DE78;

extern double lua_tonumber(void*, int);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_80196578(void*);
extern void fn_8018F81C(void*, u8);
extern int fn_801D3974(s32);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void* fn_80147EC4(void*);
extern void fn_801964E8(void*, s32, s32);
extern s32 fn_80142A70(s32, Vec3s*, s32, s32, s32, s32, s32, s32);
extern s32 fn_8014B8D0(void*, s32);
extern void* fn_801966E0(void*, int, int);

/* NonMatching: count is assumed to be at most six, as in retail and the
 * matching sibling; that caller invariant has not yet been proven here. */
s32 fn_80018708(void* script)
{
    SpawnDescriptor descriptor;
    SpawnInfo info;
    Vec3s endpoints[2];
    u8* body;
    s32 arg1;
    s32 arg2;
    s32 count;
    s32 kind;
    s32 flags;
    s32 i;
    s32 handle;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 min_z;
    f32 max_z;
    f32 best_low;
    f32 best_high;
    ValuePair values;

    arg1 = (s32)lua_tonumber(script, 1);
    arg2 = (s32)lua_tonumber(script, 2);
    count = (s32)lua_tonumber(script, 3);
    if (lua_gettop(script) != count + 4) {
        luaO_verror(script, lbl_8023CBC8, count + 2, lua_gettop(script));
        return 0;
    }

    body = descriptor.layout.body;
    flags = 0;
    kind = (s32)lua_tonumber(script, 4);
    fn_80196578(&descriptor);
    *(s16*)&descriptor.bytes[4] = -1;
    fn_8018F81C(&descriptor, (u8)count);

    *(u16*)&body[8] = 15;
    body[1] = 8;
    body[2] = (u8)count;

    values.second = values.first = fn_801D3974(kind);
    ((u8*)&values.second)[3] = (u8)arg1;
    ((u8*)&values.first)[3] = (u8)arg2;

    switch (kind) {
    case 1:
        flags = 0x20;
        break;
    case 2:
        flags = 0x08;
        break;
    case 3:
        flags = 0x10;
        break;
    case 4:
        flags = 0x40;
        break;
    case 0:
        flags = 0x100;
        break;
    }

    *(s32*)&descriptor.bytes[20] = values.second;
    *(s32*)&descriptor.bytes[24] = values.first;
    descriptor.bytes[33] = 9;
    descriptor.bytes[36] = 3;
    *(u16*)&descriptor.bytes[30] = (u16)flags;
    descriptor.bytes[44] |= 0x81;
    descriptor.bytes[43] = 0;

    endpoints[0] = *fn_80158ABC(
        fn_8015C4A4(fn_800F5C54(lua_tonumber(script, 5)), 2), 2, 0);
    endpoints[1] = *fn_80158ABC(
        fn_8015C4A4(fn_800F5C54(lua_tonumber(script, 7)), 2), 2, 0);
    dx = (f32)(endpoints[1].x - endpoints[0].x);
    dy = (f32)(endpoints[1].y - endpoints[0].y);
    dz = (f32)(endpoints[1].z - endpoints[0].z);
    min_z = (f32)endpoints[0].z;
    max_z = (f32)endpoints[0].z;
    best_low = lbl_8064DE78;
    best_high = lbl_8064DCF4;

    for (i = 0; i < count; i++) {
        Vec3s* point;
        f32 distance;

        point = fn_80158ABC(
            fn_8015C4A4(fn_800F5C54(lua_tonumber(script, i + 5)), 2),
            2, 0);
        distance = dx * point->x + dy * point->y + dz * point->z;
        if ((f32)point->z < min_z) {
            min_z = point->z;
        }
        if ((f32)point->z > max_z) {
            max_z = point->z;
        }
        if (distance > best_high) {
            best_high = distance;
            endpoints[1] = *point;
        }
        if (distance < best_low) {
            best_low = distance;
            endpoints[0] = *point;
        }
        *(Vec3s*)&body[64] = *point;
        body += 6;
    }

    *(SpawnDescriptor*)&info = descriptor;
    *(void**)&info.bytes[144] = (void*)fn_801966E0;
    info.bytes[170] = 2;
    fn_80147EC4(&info);
    if (*(void**)&info.bytes[148] != 0) {
        fn_801964E8(*(void**)&info.bytes[148], 1, 0);
    }
    script = *(void**)&info.bytes[148];
    endpoints[0].z = (s16)min_z;
    endpoints[1].z = (s16)min_z;
    handle = fn_80142A70(2, endpoints, (s16)(max_z - min_z),
                         lbl_8064D18C, 0, 0, 0, 0);
    fn_8014B8D0(script, handle);
    return 0;
}
