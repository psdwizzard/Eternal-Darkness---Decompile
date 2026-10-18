typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef union {
    u8 bytes[144];
    double align;
} SpawnDescriptor;

typedef struct {
    u8 bytes[172];
} SpawnInfo;

typedef struct {
    s32 first;
    s32 second;
} ValuePair;

extern const char lbl_8023CBC8[];

extern double lua_tonumber(void*, int);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80196578(void*);
extern void fn_8018F81C(void*, u8);
extern int fn_801D3974(s32);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void* fn_80147EC4(void*);
extern void fn_801966E0(void);

s32 fn_80018CC4(void* script)
{
    SpawnDescriptor descriptor;
    SpawnInfo info;
    s32 count;
    s32 kind;
    u8* body;
    s32 flags;
    s32 i;
    ValuePair values;

    body = &descriptor.bytes[40];
    count = (s32)lua_tonumber(script, 1);
    if (lua_gettop(script) != count + 2) {
        luaO_verror(script, lbl_8023CBC8, count + 2, lua_gettop(script));
        return 0;
    }

    kind = (s32)lua_tonumber(script, 2);
    fn_80196578(&descriptor);
    *(s16*)&descriptor.bytes[4] = -1;
    *(u16*)&descriptor.bytes[6] = 20;
    *(u16*)&descriptor.bytes[8] = 21;
    fn_8018F81C(&descriptor, (u8)count);

    *(u16*)&body[8] = 15;
    body[1] = 8;
    body[2] = (u8)count;
    values.second = values.first = fn_801D3974(kind);
    ((u8*)&values.second)[3] = 90;
    ((u8*)&values.first)[3] = 120;

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
    descriptor.bytes[44] |= 0x80;
    descriptor.bytes[43] = 0;

    for (i = 0; i < count; i++) {
        Vec3s* point = fn_80158ABC(
            fn_8015C4A4(fn_800F5C54(lua_tonumber(script, i + 3)), 2),
            2, 0);
        *(Vec3s*)&body[64] = *point;
        body += 6;
    }

    *(SpawnDescriptor*)&info = descriptor;
    *(void (**)(void))&info.bytes[144] = fn_801966E0;
    info.bytes[170] = 4;
    fn_80147EC4(&info);
    return 0;
}
