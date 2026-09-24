typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

typedef struct EffectEntry {
    u8 pad_00[0x20];
    u8 effect[0xB];
    u8 field_2B;
    u8 pad_2C[0xC];
} EffectEntry;

typedef struct EffectObject {
    u8 pad_00[0x4C];
    EffectEntry* entries;
} EffectObject;

extern ShortCoord3 lbl_80651CF0;
extern u32 lbl_806509BC;
extern float lbl_806509B8;
extern float lbl_806509C0;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];
extern void* memcpy(void*, const void*, u32);
extern void* memset(void*, int, u32);
extern void fn_80179904(void*, s16);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_80180518(void*, int, int);
extern void fn_8018EFB0(void*, u16, int);
extern unsigned int fn_800FBFB0(void);
extern void fn_8018E230(void*, u8*, int, int, s8, u8);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80182514(u8* self, void* arg1, ShortCoord3* arg2, u8* desc)
{
    u32 effect;
    ShortCoord3 base;
    ShortCoord3 setup;
    ShortCoord3 work;
    float zero;
    u32 i;
    u8 count;
    EffectEntry* item;
    u8* detail;

    detail = desc + 0x14;
    setup = lbl_80651CF0;
    item = ((EffectObject*)self)->entries;
    effect = lbl_806509BC;
    count = desc[0];
    memcpy(&setup, detail, 6);
    setup.z *= arg2->z;
    zero = lbl_806509B8;
    self[0] = 0x80;
    self[1] = desc[0];
    self[2] = desc[2];
    self[4] = desc[3];
    *((u16*)(self + 0xC)) = *((u16*)(desc + 6));
    *((s16*)(self + 0xE)) = *((s16*)(desc + 4));
    *((u16*)(self + 0xA)) = 0;
    *((u32*)(self + 0x44)) = 0;
    *((void**)(self + 0x68)) = lbl_8064D224;
    *((float*)(self + 0x3C)) = zero;
    *((float*)(self + 0x40)) = *((float*)(detail + 0x14));
    memset(self + 0x24, 0, 0x10);
    memcpy(&base, arg2, 6);
    fn_80179904(&base, *((s16*)(detail + 6)));
    fn_801804AC(self, arg1, &base, &setup);
    for (i = 0; (u8)i < count; i++) {
        memcpy(&work, &base, 6);
        fn_8018EFB0(&work, *((u16*)(detail + 8)), 0);
        fn_8018EFB0(&work, *((u16*)(detail + 8)), 1);
        work.z *= detail[0xB];
        work.z += detail[0xC] & fn_800FBFB0();
        fn_80180554(item, arg1, &work, &setup,
                    *((u16*)(desc + 8)) + (fn_800FBFB0() & 0xF), 0);
        fn_801805E0(item->effect, 4, desc[1], ((u8)i & 0x3F) * 4,
                    &effect, lbl_806509C0);
        item++;
    }

    fn_80180518(self + 0x24, 0, 1);
    item = ((EffectObject*)self)->entries;
    if (detail[0xD] == detail[0xE]) {
        item->field_2B = detail[0xE];
    } else {
        fn_8018E230(item, &item->field_2B, 1, 0, (s8)detail[0xD],
                    detail[0xE]);
    }
    if (lbl_806509B8 == *((float*)(detail + 0x14))) {
        fn_8018CB70(*((void**)(self + 0x54)), count,
                    *((u16*)(lbl_80607120 + 2)));
    } else {
        fn_8018CEC0(*((void**)(self + 0x54)), count);
    }
    fn_8018C540(*((void**)(self + 0x58)), desc + 0x10, count, 4,
                 *((u16*)(lbl_80607120 + 2)));
    if (*((s16*)(desc + 4)) >= 0) {
        fn_801F5A04(self + 0x6C, *((s16*)(desc + 4)), lbl_80606328,
                    lbl_80606318);
    }
}
