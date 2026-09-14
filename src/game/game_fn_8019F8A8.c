typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Seed {
    u32 a;
    u16 b;
} Seed;

typedef struct Header {
    u8 flags;
    u8 count;
    u8 marker;
    u8 pad;
    u8 active;
} Header;

extern u32 lbl_80651E48;
extern u16 lbl_80651E4C;
extern u32 lbl_80651E50;
extern u16 lbl_80651E54;
extern u32 lbl_8064D224;
extern u32 lbl_8064D18C;
extern float lbl_80650C88;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned long);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern void fn_801805E0(void*, int, int, int, float, void*);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern void fn_8018CB70(void*, int, int);
extern void fn_8018C540(void*, void*, int, int, int);
extern void fn_801F5A04(void*, int, void*, void*);

void fn_8019F8A8(u8* obj, void* arg1, void* arg2, u8* config)
{
    Seed seedA;
    Seed seedB;
    u8* item;
    int count = 0;
    u8 counter = 0;
    int i;
    Header* header = (Header*)obj;

    seedA.a = lbl_80651E48;
    seedA.b = lbl_80651E4C;
    seedB.a = lbl_80651E50;
    seedB.b = lbl_80651E54;
    item = *(u8**)(obj + 0x4C);

    while (counter < *(u16*)(config + 0x18)) {
        count++;
        counter++;
    }
    if ((u8)count == 0) {
        *(u16*)(obj + 0x22) = 8;
        return;
    }

    fn_801804AC(obj, arg1, &seedB, &seedA);
    header->flags = 0x80;
    header->marker = 0xFF;
    header->count = count;
    header->active = 1;
    *(s16*)(obj + 0x0E) = -1;
    *(u16*)(obj + 0x0C) = 0;
    *(u16*)(obj + 0x0A) = 0;
    *(u32*)(obj + 0x44) = 0;
    *(u32*)(obj + 0x68) = lbl_8064D224;
    *(u32*)(obj + 0x38) = lbl_8064D18C;
    memset(obj + 0x24, 0, 0x10);

    for (i = 0; i < (u8)count; item += 0x38, i++) {
        fn_80180554(item, arg1, &seedB, &seedA, 0, 0);
        fn_801805E0(item + 0x20, 4, 0, 0, lbl_80650C88, config + 0x10);
        fn_8018E230(item, item + 0x2B, 1, item[0x2B], 1, 0);
    }
    fn_8018CB70(*(void**)(obj + 0x54), count, *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(obj + 0x58), config + 0x10, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(obj + 0x0E) >= 0)
        fn_801F5A04(obj + 0x6C, *(s16*)(obj + 0x0E), lbl_80606328, lbl_80606318);
    *(u16*)(obj + 0x22) = 4;
}
