typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u32 lbl_80651E20;
extern u16 lbl_80651E24;
extern u32 lbl_80651E28;
extern u16 lbl_80651E2C;
extern u32 lbl_80651E30;
extern u16 lbl_80651E34;
extern u32 lbl_80651E38;
extern u16 lbl_80651E3C;
extern u32 lbl_8064D224;
extern float lbl_80650C58;
extern float lbl_80650C5C;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned long);
extern void fn_801804AC(void*, void*, void*, void*);
extern int fn_800FBFB0(void);
extern void fn_801805E0(void*, int, int, int, void*, float);
extern void fn_80180554(void*, void*, void*, void*, int, u16, int);
extern float fn_801790F0(float, float);
extern void fn_80180518(void*, int, int);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern void fn_8018EFB0(void*, int, int);
extern void fn_8018CB70(void*, int, int);
extern void fn_8018C540(void*, void*, int, int, int);
extern void fn_801F5A04(void*, int, void*, void*);

void fn_8019E0B0(u8* obj, s16* pos, void* arg2, u8* config)
{
    u32 initA = lbl_80651E20;
    u16 initB = lbl_80651E24;
    u32 initC = lbl_80651E28;
    u16 initD = lbl_80651E2C;
    u8 count = config[0];
    u8* item = *(u8**)(obj + 0x4C);
    u8* fields = obj + 0x8C;
    s16 bounds[8];
    s16 corners[8];
    s16 start[3];
    s16 delta[2];
    u8 seedA[6];
    u8 seedB[6];
    int i;

    *(u32*)seedA = initA;
    *(u16*)(seedA + 4) = initB;
    *(u32*)seedB = initC;
    *(u16*)(seedB + 4) = initD;
    fn_801804AC(obj, pos, seedA, seedB);

    obj[0] = 0x80;
    obj[1] = config[0];
    obj[2] = config[2];
    obj[4] = config[3];
    *(u16*)(obj + 0x0C) = *(u16*)(config + 6);
    *(s16*)(obj + 0x0E) = *(s16*)(config + 4);
    *(u16*)(obj + 0x0A) = 0;
    *(u32*)(obj + 0x44) = 0;
    *(u32*)(obj + 0x68) = lbl_8064D224;
    memset(obj + 0x24, 0, 0x10);

    {
        u16 halfW = *(u16*)(config + 0x14) >> 1;
        u16 halfH = *(u16*)(config + 0x16) >> 1;
        s16 x0 = pos[0] - halfW;
        s16 y0 = pos[1] - halfH;
        s16 x1 = pos[0] + halfW;
        s16 y1 = pos[1] + halfH;
        corners[0] = corners[2] = corners[4] = corners[6] = pos[0];
        corners[1] = corners[3] = corners[5] = corners[7] = pos[1];
        bounds[0] = x0; bounds[1] = y0;
        bounds[2] = x1; bounds[3] = y0;
        bounds[4] = x1; bounds[5] = y1;
        bounds[6] = x0; bounds[7] = y1;
        if (*(u32*)(config + 0x1C) != 0) {
            for (i = 0; i < 8; i++) corners[i] = bounds[i];
        }
    }

    *(u32*)seedA = lbl_80651E30;
    *(u16*)(seedA + 4) = lbl_80651E34;
    i = fn_800FBFB0() & 3;
    {
        int opposite = i < 2 ? i + 2 : i - 2;
        start[0] = bounds[i * 2];
        start[1] = bounds[i * 2 + 1];
        start[2] = pos[2];
        *(s16*)(fields + 0x10) = bounds[opposite * 2];
        *(s16*)(fields + 0x20) = bounds[opposite * 2 + 1];
        delta[0] = *(s16*)(fields + 0x10) - start[0];
        delta[1] = *(s16*)(fields + 0x20) - start[1];
    }
    fn_801805E0(item + 0x20, 4, (u8)(config[1] - (fn_800FBFB0() & 0xF)), 0, lbl_802FC5BC + 0xC, lbl_80650C58);
    fn_80180554(item, start, delta, seedB, 0, (u16)(*(u16*)(config + 8) + (fn_800FBFB0() & 0x7F) + 1000), 0);
    *(float*)(fields + 0x30) = *(float*)(fields + 0x50) = fn_801790F0((float)delta[1], (float)delta[0]) - lbl_80650C5C;
    fn_80180518(obj + 0x24, 0, 1);
    fn_8018E230(item, item + 0x2B, 1, 0, 5, 250);

    i = 1;
    {
    float angleOffset = lbl_80650C5C;
    for (item += 0x38; i < count; i++, item += 0x38) {
        int corner;
        *(u32*)seedA = lbl_80651E38;
        *(u16*)(seedA + 4) = lbl_80651E3C;
        corner = (fn_800FBFB0() & 3) * 2;
        start[0] = corners[corner];
        start[1] = corners[corner + 1];
        start[2] = pos[2];
        fn_8018EFB0(seedA, 2, 0);
        fn_8018EFB0(seedA, 2, 1);
        if (*(s16*)seedA == 0) *(s16*)seedA = 1;
        if (*(s16*)(seedA + 2) == 0) *(s16*)(seedA + 2) = 1;
        fn_80180554(item, start, seedA, seedB, 0, (u16)(*(u16*)(config + 8) + (fn_800FBFB0() & 0x7F) + 1000), 0);
        fn_801805E0(item + 0x20, 4, (u8)(config[1] - (fn_800FBFB0() & 0xF)), i << 2, lbl_802FC5BC + 0xC, lbl_80650C58);
        *(s16*)(fields + 0x10 + i * 2) = start[0] + (*(s16*)seedA << 4);
        *(s16*)(fields + 0x20 + i * 2) = start[1] + (*(s16*)(seedA + 2) << 4);
        *(float*)(fields + 0x30 + i * 4) = *(float*)(fields + 0x50 + i * 4) =
            fn_801790F0((float)*(s16*)(seedA + 2), (float)*(s16*)seedA) - angleOffset;
        fn_80180518(obj + 0x24, i, 1);
        fn_8018E230(item, item + 0x2B, 1, 0, 5, 250);
    }
    }
    fn_8018CB70(*(void**)(obj + 0x54), count, *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(obj + 0x58), lbl_802FC5BC + 0xC, count, 4, *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0)
        fn_801F5A04(obj + 0x6C, *(s16*)(config + 4), lbl_80606328, lbl_80606318);
}
