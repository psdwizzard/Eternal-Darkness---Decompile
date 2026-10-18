typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectInfo {
    u8 type;
    u8 count;
    u8 pad02[2];
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[0xE];
    u32 word18;
    u8 pad1C[3];
    u8 value1F;
    u8 pad20[0x74];
} EffectInfo;

typedef struct BurstInfo {
    u8 count;
    u8 enabled;
    u8 color0;
    s8 color1;
    u16 value04;
    u16 value06;
    u8 pad08[0xC];
    u8 color14;
    u8 color15;
    u8 color16;
    u8 pad17[2];
    s8 color19;
    u8 pad1A[2];
    u32 word1C;
    u8 pad20[0x14];
    float scale34;
    u8 pad38[4];
    u8 flag3C;
    u8 color3D;
    u8 color3E;
    u8 pad3F[0x51];
    void (*callback90)(void);
    u8 pad94[4];
    Vec3 position98;
    u8 padA4[6];
    u8 modeAA;
    u8 padAB[5];
} BurstInfo;

typedef struct GameObject {
    u8 pad00[4];
    u32 owner;
    int type;
    u8 pad0C[0x24];
    void* link30;
    u8 pad34[4];
    Vec3 position;
    void* resource44;
    u8 pad48[0xFA8];
    u8 flagsFF0;
    u8 padFF1[3];
    u16 stateFF4;
} GameObject;

extern int lbl_8064D18C;
extern void fn_801FE22C(void*);
extern void fn_801D31E0(GameObject*);
extern void fn_80181F5C(EffectInfo*);
extern s16 fn_801D3A34(u32, int);
extern s16 fn_801CEB2C(u32);
extern float sinf(float);
extern float cosf(float);
extern u32 rand(void);
extern void* fn_80148008(Vec3*, s16*, EffectInfo*, void (*)(void));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern void fn_80182014(void);
extern void fn_80181FD8(void);
extern void* fn_800CE9A4(u8*, int, int);
extern void fn_801E8328(int, void*);
extern void fn_80182380(EffectInfo*);
extern void fn_80182448(void);
extern void fn_8019B13C(BurstInfo*);
extern void fn_8019AD40(void);
extern void fn_80147EC4(BurstInfo*);

void fn_801D324C(void* arg)
{
    GameObject* object = arg;
    EffectInfo info;
    Vec3 work0;
    Vec3 work2E;
    Vec3 work42;
    Vec3 work56;
    Vec3 position0;
    Vec3 position2E;
    Vec3 position42;
    Vec3 position56;
    u32 owner;
    s16 count;
    int i;
    BurstInfo burst;

    if (object->type != lbl_8064D18C) {
        fn_801FE22C(object->resource44);
        fn_801D31E0(object);
    } else {
        s16 range[3] = { 0, 0, 1 };

        switch (object->stateFF4) {
        case 0: {
            u8 color[4] = { 60, 60, 60, 120 };

            if (object->flagsFF0 & 4) {
                object->link30 = fn_800CE9A4(color, 10, 0);
                if (object->link30 != 0)
                    fn_801E8328(13, object->link30);
            }

            owner = object->owner;
            fn_80182380(&info);
            info.type = 8;
            info.count = 1;
            info.value04 = fn_801D3A34(owner, 0x42);
            info.value06 = 30;
            info.value08 = 8;
            info.value1F = 2;
            count = fn_801CEB2C(owner);
            for (i = 0; i < count; i++) {
                float angle = 6.2831855f * i / count;
                work0.x = object->position.x + 250.0f * sinf(angle);
                work0.y = object->position.y + 250.0f * cosf(angle);
                work0.z = object->position.z;
                position0 = work0;
                {
                    void* effect = fn_80148008(&position0, range,
                                                &info, fn_80182448);
                    if (effect != 0)
                        fn_8017FF1C(fn_80156938(effect), 4);
                }
            }

            fn_8019B13C(&burst);
            burst.count = count;
            burst.enabled = 0;
            burst.value04 = fn_801D3A34(owner, 0x31);
            burst.value06 = 0;
            burst.color0 = 0xFC;
            burst.color1 = -6;
            burst.color16 = 0;
            burst.color14 = 0xF0;
            burst.color15 = 0x96;
            burst.color19 = -10;
            burst.scale34 = 0.0f;
            burst.word1C = 0;
            burst.flag3C = 1;
            burst.color3D = 0xFC;
            burst.color3E = 12;
            burst.callback90 = fn_8019AD40;
            burst.position98 = object->position;
            burst.position98.z += 5.0f;
            burst.modeAA = 4;
            fn_80147EC4(&burst);
            break;
        }
        case 0x2E: {
            s16 range2E[3];

            owner = object->owner;
            fn_80181F5C(&info);
            info.count = 2;
            info.value04 = fn_801D3A34(owner, 0x42);
            info.word18 = 0;
            count = fn_801CEB2C(owner);
            for (i = 0; i < count; i++) {
                float angle = 6.2831855f * i / count;
                work2E.x = object->position.x + 250.0f * sinf(angle);
                work2E.y = object->position.y + 250.0f * cosf(angle);
                work2E.z = object->position.z;
                info.type = (rand() & 7) + 10;
                range2E[1] = 0;
                range2E[0] = 0;
                range2E[2] = (rand() & 3) + 10;
                position2E = work2E;
                {
                    void* effect = fn_80148008(&position2E, range2E, &info, fn_80182014);
                    if (effect != 0)
                        fn_8017FF1C(fn_80156938(effect), 4);
                }
            }
            break;
        }
        case 0x42: {
            s16 range42[3];

            owner = object->owner;
            fn_80181F5C(&info);
            info.count = 2;
            info.value04 = fn_801D3A34(owner, 0x42);
            info.word18 = 0;
            count = fn_801CEB2C(owner);
            for (i = 0; i < count; i++) {
                float angle = 6.2831855f * i / count;
                work42.x = object->position.x + 250.0f * sinf(angle);
                work42.y = object->position.y + 250.0f * cosf(angle);
                work42.z = object->position.z;
                info.type = (rand() & 7) + 5;
                range42[1] = 0;
                range42[0] = 0;
                range42[2] = (rand() & 3) + 8;
                position42 = work42;
                {
                    void* effect = fn_80148008(&position42, range42, &info, fn_80182014);
                    if (effect != 0)
                        fn_8017FF1C(fn_80156938(effect), 4);
                }
            }
            break;
        }
        case 0x56:
            owner = object->owner;
            fn_80181F5C(&info);
            info.count = 2;
            info.value04 = fn_801D3A34(owner, 0x42);
            info.word18 = 0;
            count = fn_801CEB2C(owner);
            for (i = 0; i < count; i++) {
                float angle = 6.2831855f * i / count;
                work56.x = object->position.x + 250.0f * sinf(angle);
                work56.y = object->position.y + 250.0f * cosf(angle);
                work56.z = object->position.z;
                info.type = (rand() & 3) + 4;
                position56 = work56;
                {
                    void* effect = fn_80148008(&position56, range,
                                                &info, fn_80181FD8);
                    if (effect != 0)
                        fn_8017FF1C(fn_80156938(effect), 4);
                }
            }
            fn_801D31E0(object);
            break;
        }
    }
}
