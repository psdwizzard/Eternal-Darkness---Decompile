typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct ShortCoord3 { s16 x, y, z; } ShortCoord3;
typedef struct Fields {
    u8 padding[0x10];
    s16 x[8];
    s16 y[8];
    float angle[8];
    float previousAngle[8];
} Fields;

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
extern const float lbl_80650C5C;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned long);
extern void fn_801804AC(void*, void*, void*, void*);
extern u32 rand(void);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_80180554(void*, void*, void*, void*, u16, u16);
extern float fn_801790F0(float, float);
extern void fn_80180518(void*, u8, int);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern void fn_8018EFB0(void*, u16, int);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, const void*, u8, int, u16);
extern void fn_801F5A04(void*, int, void*, void*);

void fn_8019E0B0(u8* obj, s16* pos, void* arg2, u8* config)
{
    u8 i;
    u8 count;
    Fields* fields;
    u8* item;
    s16 corners[8];
    s16 bounds[8];
    u8 seedA[6];
    u8 seedB[6];
    s16 delta[3];
    ShortCoord3 start;
    int selectedCorner;

    *(u32*)seedA = lbl_80651E20;
    *(u16*)(seedA + 4) = lbl_80651E24;
    *(u32*)seedB = lbl_80651E28;
    *(u16*)(seedB + 4) = lbl_80651E2C;
    count = config[0];
    item = *(u8**)(obj + 0x4C);
    fn_801804AC(obj, pos, seedA, seedB);

    fields = (Fields*)(obj + 0x8C);
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
        corners[0] = pos[0];
        corners[1] = pos[1];
        corners[2] = pos[0];
        corners[3] = pos[1];
        corners[4] = pos[0];
        corners[5] = pos[1];
        corners[6] = pos[0];
        corners[7] = pos[1];
        bounds[0] = x0; bounds[1] = y0;
        bounds[2] = x1; bounds[3] = y0;
        bounds[4] = x1; bounds[5] = y1;
        bounds[6] = x0; bounds[7] = y1;
        if (*(int*)(config + 0x1C) != 0) {
            for (selectedCorner = 0; selectedCorner < 8; selectedCorner++) corners[selectedCorner] = bounds[selectedCorner];
        }
    }

    /* Keep the seed's third component: fn_80180554 copies all three shorts. */
    *(u32*)delta = lbl_80651E30;
    *(u16*)(delta + 2) = lbl_80651E34;
    selectedCorner = rand() & 3;
    {
        int opposite = selectedCorner + 2;
        s16 y, x;
        if (selectedCorner >= 2) opposite = selectedCorner - 2;
        x = bounds[selectedCorner * 2];
        y = bounds[selectedCorner * 2 + 1];
        start.x = x;
        start.y = y;
        start.z = pos[2];
        fields->x[0] = bounds[opposite * 2];
        fields->y[0] = bounds[opposite * 2 + 1];
        delta[0] = fields->x[0] - x;
        delta[1] = fields->y[0] - y;
    }
    fn_801805E0(item + 0x20, 4, (u8)(config[1] - (rand() & 0xF)), 0, lbl_802FC5BC + 0xC, lbl_80650C58);
    fn_80180554(item, &start, delta, seedB, (u16)(1000 + *(u16*)(config + 8) + (rand() & 0x7F)), 0);
    fields->previousAngle[0] = fields->angle[0] = fn_801790F0((float)delta[1], (float)delta[0]) - lbl_80650C5C;
    fn_80180518(obj + 0x24, 0, 1);
    fn_8018E230(item, item + 0x2B, 1, 0, 5, 250);

    {
        i = 1;
        for (item += 0x38; i < count; item += 0x38, i++) {
            u8 seedA[6];
            ShortCoord3 start;
            s16* corner;
            *(u32*)seedA = lbl_80651E38;
            *(u16*)(seedA + 4) = lbl_80651E3C;
            corner = corners + (rand() & 3) * 2;
            start.x = corner[0];
            start.y = corner[1];
            start.z = pos[2];
            fn_8018EFB0(seedA, 2, 0);
            fn_8018EFB0(seedA, 2, 1);
            if (*(s16*)seedA == 0) *(s16*)seedA = 1;
            if (*(s16*)(seedA + 2) == 0) *(s16*)(seedA + 2) = 1;
            fn_80180554(item, &start, seedA, seedB, (u16)(1000 + *(u16*)(config + 8) + (rand() & 0x7F)), 0);
            fn_801805E0(item + 0x20, 4, (u8)(config[1] - (rand() & 0xF)), (i & 0x3F) << 2, lbl_802FC5BC + 0xC, lbl_80650C58);
            fields->x[i] = start.x + (*(s16*)seedA * 16);
            fields->y[i] = start.y + (*(s16*)(seedA + 2) * 16);
            fields->previousAngle[i] = fields->angle[i] =
                fn_801790F0((float)*(s16*)(seedA + 2), (float)*(s16*)seedA) - lbl_80650C5C;
            fn_80180518(obj + 0x24, i, 1);
            fn_8018E230(item, item + 0x2B, 1, 0, 5, 250);
        }
    }
    fn_8018CB70(*(void**)(obj + 0x54), count, *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(obj + 0x58), lbl_802FC5BC + 0xC, count, 4, *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0)
        fn_801F5A04(obj + 0x6C, *(s16*)(config + 4), lbl_80606328, lbl_80606318);
}
