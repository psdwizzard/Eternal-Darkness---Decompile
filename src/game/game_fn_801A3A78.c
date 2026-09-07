typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

extern u32 lbl_80651E80;
extern u16 lbl_80651E84;
extern u32 lbl_80650D48;
extern u32 lbl_8064D224;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];
extern const float lbl_80650D44;
extern const float lbl_80650D4C;
extern const float lbl_80650D50;
extern float lbl_80650D54;

extern void fn_801804AC(void*, void*, void*, void*);
extern void* memset(void*, int, unsigned long);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern void fn_80180518(void*, int, int);
extern void fn_801805E0(void*, int, u8, int, float, void*);
extern void fn_8018CEC0(void*, int);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_801A3A78(u8* object, void* coordinate, void* descriptor, u8* owner)
{
    u8 color[6];
    s16 position[3];
    u8 count;
    u8* entry;
    u8* texture;
    u32 fallback;
    int i;

    *(u32*)color = lbl_80651E80;
    *(u16*)(color + 4) = lbl_80651E84;
    fallback = lbl_80650D48;
    count = owner[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, coordinate, descriptor, color);
    object[0] = 0x80;
    object[1] = count;
    object[2] = owner[2];
    object[4] = owner[3];
    *(s16*)(object + 0xE) = *(s16*)(owner + 4);
    *(u32*)(object + 0x68) = lbl_8064D224;
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x38) = *(u32*)(owner + 0x20);
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3C) = lbl_80650D44;
    *(float*)(object + 0x40) = lbl_80650D4C;

    if (owner[0x3D] == 0) {
        texture = lbl_802FC5BC + 0xC;
    } else {
        texture = (u8*)&fallback;
    }
    memset(object + 0x24, 0, 0x10);
    for (i = 0; (u8)i < count; i++) {
        float fraction = lbl_80650D50 * (float)(u8)i / (float)count;
        float x = fn_80048C2C(fraction);
        position[0] = (s16)((float)*(s16*)(owner + 0x34) * x + *(float*)(owner + 0x24));
        x = fn_80048C50(fraction);
        position[1] = (s16)((float)*(s16*)(owner + 0x34) * x + *(float*)(owner + 0x28));
        position[2] = (s16)*(float*)(owner + 0x2C);
        fn_80180554(entry, position, descriptor, color, 0, 0);
        if (owner[0x3D] == 0)
            fn_80180518(object + 0x24, i, 1);
        fn_801805E0(entry + 0x20, 4, owner[1], 0, lbl_80650D54, texture);
        entry += 0x38;
    }
    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), lbl_802FC5BC + 0xC, count, 4, *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(owner + 4) >= 0)
        fn_801F5A04(object + 0x6C, *(s16*)(owner + 4), lbl_80606328, lbl_80606318);
}
