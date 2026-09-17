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
void fn_80151D00(u8* instance)
{
    u8* work = instance + 8;
    Vec3f position0;
    Vec3f position1;
    u8 key0[8];
    u8 key1[8];
    u8 key2[8];
    u32 effect_key;
    u8 descriptor[0x94];

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
        fn_8019B13C(descriptor);
        descriptor[1] = 1;
        descriptor[2] = 0xF5;
        descriptor[3] = (u8)-7;
        *(u16*)(descriptor + 4) = *(s16*)(work + 0x0E);
        *(u16*)(descriptor + 6) = *(u16*)(work + 0x18) - END + 20;
        descriptor[0x16] = 7;
        descriptor[0x17] = 0xF5;
        *(u32*)(descriptor + 0x1C) = 0;
        *(u32*)(descriptor + 0x20) = 0;
        *(u32*)(descriptor + 0x28) = 1;
        *(float*)(descriptor + 0x34) = lbl_80650584;
        *(u32*)(descriptor + 0x38) = *(u32*)(work + 0x24);
        position1 = *(Vec3f*)(work + 0x2C);
        if (fn_80148008(&position1, key0, descriptor, fn_8019ADE4) != 0) {
            void* object = fn_80156938();
            fn_8017FF1C(object, 2);
            fn_8017FE1C(object, fn_8018B058);
            *(void**)(work + 0x254) = object;
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
        u8* command;
        Vec3s* object_position;
        *(u32*)key1 = lbl_80651C40;
        *(u16*)(key1 + 4) = lbl_80651C44;
        command = work + 0x1A4;
        fn_8019A3A4(command);
        *(u16*)(command + 4) = *(s16*)(work + 0x10);
        *(u16*)(command + 6) = *(u16*)(work + 0x14) - 20;
        *(void**)(command + 0x14) = *(void**)(work + 0x254);
        *(u32*)(command + 0x18) = *(u32*)(work + 0x24);
        *(void (**)(void))(command + 0x90) = fn_8019A300;
        object_position = fn_8017FDA8(*(void**)(work + 0x254), 0);
        *(float*)(command + 0x98) = object_position->x;
        *(float*)(command + 0x9C) = object_position->y;
        *(float*)(command + 0xA0) = object_position->z;
        memcpy(command + 0xA4, key1, 6);
        *(u32*)(command + 0x94) = 0;
        command[0xAA] = 2;
        fn_801E8328(0x10, command);
    }

    if (*(s32*)(instance + 0x1324) == lbl_8064D18C) {
        if (FRAME == 0) {
            u8* command;
            *(u32*)key2 = lbl_80651C48;
            *(u16*)(key2 + 4) = lbl_80651C4C;
            command = work + 0x44;
            fn_80199EBC(command);
            *(u16*)(command + 6) = END - 10;
            *(u16*)(command + 4) = *(s16*)(work + 0x0E);
            *(u16*)(command + 0x20) = *(float*)(work + 0x2C);
            *(u16*)(command + 0x22) = *(float*)(work + 0x30);
            *(u16*)(command + 0x24) = *(float*)(work + 0x34);
            *(u32*)(command + 0x2C) = *(u32*)(work + 0x24);
            *(void (**)(void))(command + 0x90) = fn_80199E18;
            memcpy(command + 0xA4, key2, 6);
            *(u32*)(command + 0x94) = 0;
            command[0xAA] = 4;
            fn_801E8328(0x10, command);
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
