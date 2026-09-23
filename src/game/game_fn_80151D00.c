/* NonMatching: independent reconstruction of the 0x80151D00 event callback. */
#include "src/game/types.h"
typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct EffectDescriptor {
    u8 unknown0;
    u8 enabled;
    u8 kind;
    s8 mode;
    s16 resource;
    u16 duration;
    u8 unknown08[0x0E];
    u8 flags;
    u8 kind2;
    u8 unknown18[4];
    u32 field1C;
    u32 field20;
    u32 field24;
    u32 field28;
    u8 unknown2C[8];
    float scale;
    u32 field38;
    u8 unknown3C[0x58];
} EffectDescriptor;

#define FRAME (*(u16*)(instance + 0x132C))
#define END (*(u16*)(work + 0x12))

extern u32 lbl_80651C38;
extern u16 lbl_80651C3C;
extern u32 lbl_80651C40;
extern u16 lbl_80651C44;
extern u32 lbl_80651C48;
extern u16 lbl_80651C4C;
extern float lbl_80650584;
extern s32 lbl_8064D18C;

extern void fn_80199128(void*, s32);
extern unsigned long long fn_8020123C();
extern void fn_8019B134(void*, s32);
extern void fn_8019B13C(void*);
extern void* fn_80148008(Vec3f*, void*, void*, void (*)(void));
extern void fn_8019ADE4(void);
extern void *fn_80156938();
extern void fn_8017FF1C(void*, s32);
extern void fn_8017FE1C(void*, void (*)(void));
extern void fn_8018B058(void);
extern void fn_801809B8(void*, u8);
extern void fn_80152260(s32, void*, Vec3f*, u16, u16, s32, u32, u32, void*, u16);
extern void fn_8019A3A4(void*);
extern void fn_8019A300(void);
extern Vec3s* fn_8017FDA8(void*, s32);
extern void* memcpy(void*, const void*, u32);
extern int fn_801E8328();
extern void fn_80199EBC(void*);
extern void fn_80199E18(void);
extern void fn_8014F700(Vec3f*, s16, void*);
extern void fn_80149E28(void*);
void fn_80151D00(u8* arg)
{
    u8* work = arg + 8;
    u8* instance = arg;
    Vec3f position0;
    Vec3f position1;
    u8 key0[8];
    u8 key1[8];
    u8 key2[8];
    u32 effect_key;
    EffectDescriptor descriptor;

    if (*(s32*)(instance + 8) != 0 && *(s32*)(work + 4) == 0) {
        *(u16*)(work + 0x18) = *(u16*)(instance + 0x132C) + *(u16*)(work + 0x16);
        if (*(void**)(work + 0x238) != 0)
            fn_80199128(*(void**)(work + 0x238), 0);
        *(u16*)(work + 0x1E) = *(u16*)(work + 0x18) - 50;
        if (*(s32*)(work + 0x28) > 0)
            fn_8020123C(0xE2, *(s32*)(work + 0x28), *(s32*)(work + 0x28), 0);
        *(s32*)(work + 4) = 1;
    }

    if (*(void**)(work + 0x254) != 0 && FRAME == *(u16*)(work + 0x1E))
        fn_8019B134(*(void**)(work + 0x254), 0);

    if (FRAME == END - 60) {
        *(u32*)key0 = lbl_80651C38;
        *(u16*)(key0 + 4) = lbl_80651C3C;
        fn_8019B13C(&descriptor);
        descriptor.enabled = 1;
        descriptor.duration = *(u16*)(work + 0x18) - END + 20;
        descriptor.resource = *(s16*)(work + 0x0E);
        descriptor.kind = 0xF5;
        descriptor.mode = -7;
        descriptor.field1C = 0;
        descriptor.field20 = 0;
        descriptor.flags = 7;
        descriptor.kind2 = 0xF5;
        descriptor.scale = lbl_80650584;
        descriptor.field38 = *(u32*)(work + 0x24);
        descriptor.field28 = 1;
        position1 = *(Vec3f*)(work + 0x2C);
        if (fn_80148008(&position1, key0, &descriptor, fn_8019ADE4) != 0) {
            arg = fn_80156938();
            fn_8017FF1C(arg, 2);
            fn_8017FE1C(arg, fn_8018B058);
            *(void**)(work + 0x254) = arg;
        }
    } else if (FRAME >= END - 58 && FRAME <= END - 10 && *(void**)(work + 0x254) != 0) {
        fn_801809B8(*(void**)(work + 0x254), FRAME - (END - 56));
    }

    if (FRAME >= *(u16*)(work + 0x18) - 50) {
        s32 delta = *(u16*)(work + 0x18) - FRAME - 1;
        u8 value = 0 > delta ? 0 : delta;
        if (*(void**)(work + 0x254) != 0 && value != 0)
            fn_801809B8(*(void**)(work + 0x254), value);
    }

    if (FRAME == END) {
        s32 amount = *(s32*)(work + 0x28);
        void* optional = 0;
        if (amount > 0)
            optional = work;
        fn_80152260(*(s32*)(instance + 0x1324), *(void**)(work + 0x20),
                     (Vec3f*)(work + 0x38), 50, *(u16*)(work + 0x14),
                     (s32)*(void**)(work + 0x254),
                     *(u32*)(work + 0x24), amount, optional,
                     *(u16*)(work + 0x0A));
    } else if (FRAME == END + 10 && *(s32*)work == 0) {
        Vec3s* object_position;
        *(u32*)key1 = lbl_80651C40;
        *(u16*)(key1 + 4) = lbl_80651C44;
        arg = work + 0x1A4;
        fn_8019A3A4(arg);
        *(u16*)(arg + 4) = *(s16*)(work + 0x10);
        *(u16*)(arg + 6) = *(u16*)(work + 0x14) - 20;
        *(void**)(arg + 0x14) = *(void**)(work + 0x254);
        *(u32*)(arg + 0x18) = *(u32*)(work + 0x24);
        *(void (**)(void))(arg + 0x90) = fn_8019A300;
        object_position = fn_8017FDA8(*(void**)(work + 0x254), 0);
        *(float*)(arg + 0x98) = object_position->x;
        *(float*)(arg + 0x9C) = object_position->y;
        *(float*)(arg + 0xA0) = object_position->z;
        memcpy(arg + 0xA4, key1, 6);
        *(u32*)(arg + 0x94) = 0;
        arg[0xAA] = 2;
        fn_801E8328(0x10, arg);
    }

    if (*(s32*)(instance + 0x1324) == lbl_8064D18C) {
        if (FRAME == 0) {
            *(u32*)key2 = lbl_80651C48;
            *(u16*)(key2 + 4) = lbl_80651C4C;
            arg = work + 0x44;
            fn_80199EBC(arg);
            *(u16*)(arg + 6) = END - 10;
            *(u16*)(arg + 4) = *(s16*)(work + 0x0E);
            *(u16*)(arg + 0x20) = *(float*)(work + 0x2C);
            *(u16*)(arg + 0x22) = *(float*)(work + 0x30);
            *(u16*)(arg + 0x24) = *(float*)(work + 0x34);
            *(u32*)(arg + 0x2C) = *(u32*)(work + 0x24);
            *(void (**)(void))(arg + 0x90) = fn_80199E18;
            memcpy(arg + 0xA4, key2, 6);
            *(u32*)(arg + 0x94) = 0;
            arg[0xAA] = 4;
            fn_801E8328(0x10, arg);
        }
        if (FRAME == *(u16*)(work + 0x1A) || FRAME == *(u16*)(work + 0x1A) + 10 ||
            FRAME == *(u16*)(work + 0x1A) + 20) {
            Vec3s* object_position = fn_8017FDA8(*(void**)(work + 0x254), 0);
            position0.x = object_position->x;
            position0.y = object_position->y;
            position0.z = object_position->z;
            effect_key = *(u32*)(work + 0x258);
            fn_8014F700(&position0, *(s16*)(work + 0x0C), &effect_key);
        }
    }

    if (FRAME == *(u16*)(work + 0x1A) + 20)
        *(u16*)(work + 0x1A) += 0x8D;

    if (*(s32*)(work + 0x28) > 0) {
        if (*(s32*)work != 0 && FRAME == *(u16*)(work + 0x18))
            fn_80149E28(instance);
    } else if (FRAME == *(u16*)(work + 0x18)) {
        fn_80149E28(instance);
    }
}
