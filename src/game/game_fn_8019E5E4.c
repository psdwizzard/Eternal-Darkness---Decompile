typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern u8 lbl_8064D258;
extern float lbl_80650C5C, lbl_80650C68, lbl_80650C6C, lbl_80650C70;
extern u8 fn_8018E26C(void*, void*);
extern void fn_80180518(u8*, u8, int);
extern int fn_80179064(int, int, int, int);
extern void fn_8018EFB0(void*, int, int);
extern float fn_801790F0(float, float);
extern void fn_8017A12C(float*, float, float);
extern int fn_8017A010(float*, int, float, float, float);
extern void fn_80179904(void*, s16);
extern int rand(void);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern int fn_80180454(void*);

int fn_8019E5E4(u8* obj)
{
    u8* pos;
    u8* angle;
    int count;
    u8* bounds;
    u8* item;
    int i;

    bounds = obj + 0x8C;
    i = 0;
    pos = bounds;
    angle = bounds;
    item = *(u8**)(obj + 0x4C);
    count = obj[1];

    for (; i < count;) {
        if (item[0] != 0 && !fn_8018E26C(item, item + 0x2B) &&
            *(u16*)(obj + 0x0A) >= *(u16*)(item + 8))
            fn_80180518(obj + 0x24, (u8)i, 0);

        if (fn_80179064(*(s16*)(item + 0x0A), *(s16*)(item + 0x0C),
                       *(s16*)(pos + 0x10), *(s16*)(pos + 0x20)) <= 30) {
            fn_8018EFB0(item + 0x10, 0x40, 0);
            fn_8018EFB0(item + 0x10, 0x40, 1);
            *(s16*)(pos + 0x10) = *(s16*)(item + 0x0A) + *(s16*)(item + 0x10);
            *(s16*)(pos + 0x20) = *(s16*)(item + 0x0C) + *(s16*)(item + 0x12);
            if (*(s16*)(pos + 0x10) > *(s16*)(bounds + 8) || *(s16*)(pos + 0x10) < *(s16*)(bounds + 0x0A))
                *(s16*)(pos + 0x10) = *(s16*)(obj + 0x10);
            if (*(s16*)(pos + 0x20) > *(s16*)(bounds + 0x0C) || *(s16*)(pos + 0x20) < *(s16*)(bounds + 0x0E))
                *(s16*)(pos + 0x20) = *(s16*)(obj + 0x12);
            *(s16*)(item + 0x10) = *(s16*)(pos + 0x10) - *(s16*)(item + 0x0A);
            *(s16*)(item + 0x12) = *(s16*)(pos + 0x20) - *(s16*)(item + 0x0C);
            *(s16*)(item + 0x14) = 0;
            *(float*)(angle + 0x50) = fn_801790F0((float)*(s16*)(item + 0x12), (float)*(s16*)(item + 0x10)) - lbl_80650C5C;
        } else {
            float difference;
            float magnitude;
            fn_8017A12C(&difference, *(float*)(angle + 0x30), *(float*)(angle + 0x50));
            magnitude = difference < lbl_80650C68 ? -difference : difference;
            if (magnitude > lbl_80650C6C)
                fn_8017A010((float*)(angle + 0x30), 0, *(float*)(angle + 0x50), lbl_80650C70, lbl_80650C6C);
            *(s16*)(item + 0x10) = *(s16*)(pos + 0x10) - *(s16*)(item + 0x0A);
            *(s16*)(item + 0x12) = *(s16*)(pos + 0x20) - *(s16*)(item + 0x0C);
            *(s16*)(item + 0x14) = 0;
            fn_80179904(item + 0x10, 2);
            *(s16*)(item + 0x0A) += *(s16*)(item + 0x10) + (1 - (rand() & 1));
            *(s16*)(item + 0x0C) += *(s16*)(item + 0x12) + (1 - (rand() & 1));
            *(s16*)(item + 0x0E) += *(s16*)(item + 0x14);
        }
        if (*(u16*)(obj + 0x0A) == *(u16*)(item + 8))
            fn_8018E230(item, item + 0x2B, 1, obj[2], obj[4], 0);
        item += 0x38;
        pos += 2;
        angle += 4;
        i++;
    }
    *(u16*)(obj + 0x0A) += 1;
    if (fn_80180454(obj + 0x24) || *(u16*)(obj + 0x0A) >= 0x800) {
        *(u16*)(obj + 0x22) = 8;
        lbl_8064D258 = 0;
    }
    return 0;
}
