typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

extern u32 lbl_80651D38;
extern u16 lbl_80651D3C;
extern void* lbl_8064D224;
extern float lbl_80650A18;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void fn_80179904(void*, s16);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180518(void*, u32, int);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_8018C2D0(void*, u8, int);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80185CA4(u8* self, void* arg1, void* arg2, u8* desc)
{
    register u8 count;
    register u8* desc_local;
    register void* arg1_local;
    register u8* self_local;
    register int i;
    register u8* entry;
    SixBytes setup;

    desc_local = desc;
    arg1_local = arg1;
    self_local = self;

    setup.word = lbl_80651D38;
    setup.half = lbl_80651D3C;
    entry = *(u8**)(self_local + 0x4C);
    count = desc_local[0];
    fn_801804AC(self_local, arg1_local, arg2, &setup);

    self_local[0] = 0x80;
    self_local[1] = desc_local[0];
    *(u16*)(self_local + 0xC) = *(u16*)(desc_local + 6);
    *(s16*)(self_local + 0xE) = *(s16*)(desc_local + 4);
    *(u16*)(self_local + 0xA) = 0;
    *(u32*)(self_local + 0x44) = 0;
    self_local[2] = desc_local[2];
    self_local[4] = desc_local[3];
    *(void**)(self_local + 0x68) = lbl_8064D224;
    memset(self_local + 0x24, 0, 0x10);
    fn_80179904(self_local + 0x16, *(s16*)(desc_local + 0x20));

    for (i = 0; (u8)i < count; i++) {
        fn_80180554(entry, arg1_local, self_local + 0x16, &setup,
                    *(u16*)(desc_local + 8), 0);
        fn_801805E0(entry + 0x20, 2, desc_local[1], (i & 0x7F) << 1,
                    desc_local + 0x78, lbl_80650A18);
        fn_80180518(self_local + 0x24, i, 1);
        entry += 0x38;
    }

    fn_8018C2D0(*(void**)(self_local + 0x54), count, desc_local[0x19]);
    fn_8018C540(*(void**)(self_local + 0x58), desc_local + 0x78, count, 2,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(desc_local + 4) >= 0) {
        fn_801F5A04(self_local + 0x6C, *(s16*)(desc_local + 4),
                    lbl_80606328, lbl_80606318);
    }
}
