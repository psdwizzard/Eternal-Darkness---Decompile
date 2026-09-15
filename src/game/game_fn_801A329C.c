typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u32 lbl_80651E68;
extern u16 lbl_80651E6C;
extern u8 lbl_80607440[];
extern u8 lbl_80607120[];
extern u32 lbl_8064D18C;
extern float lbl_80650D10;

extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, int, void*, float);
extern void fn_80180518(void*, u8, int);
extern void fn_8018CB70(void*, u8, u16);
extern u32 fn_80048630(void);
extern u32 fn_80048640(void);
extern u32 fn_80048650(void);
extern u32 fn_800FBFB0(void);
extern void fn_801F5A04(void*, s16, u32, u32);
extern void* memset(void*, int, u32);

void fn_801A329C(u8* object, void* arg0, void* arg1, u8* descriptor)
{
    u8 local[6];
    u8* entry;
    u8 count;
    u8 i;
    u8 random_base;

    *(u32*)local = lbl_80651E68;
    *(u16*)(local + 4) = lbl_80651E6C;
    entry = *(u8**)(object + 0x4C);
    count = descriptor[0];
    fn_801804AC(object, arg0, arg1, local);

    object[0] = 0x80;
    object[1] = descriptor[0];
    object[2] = descriptor[2];
    object[4] = descriptor[3];
    *(u16*)(object + 0xC) = *(u16*)(descriptor + 6);
    *(s16*)(object + 0xE) = *(s16*)(descriptor + 4);
    *(u16*)(object + 0xA) = 0;
    object[5] = 0;
    *(u32*)(object + 0x44) = 0;
    *(u32*)(object + 0x68) = fn_80048630();
    *(u32*)(object + 0x38) = lbl_8064D18C;
    object[3] |= 0x81;
    memset(object + 0x24, 0, 0x10);

    for (i = 0; i < count; i++) {
        fn_80180554(entry, arg0, arg1, local, *(u16*)(descriptor + 8), 0);
        random_base = descriptor[1];
        fn_801805E0(entry + 0x20, 4,
                    (u8)(random_base - ((random_base - 1) & fn_800FBFB0()) + 4),
                    (i & 0x3F) * 4, lbl_80607440, lbl_80650D10);
        fn_80180518(object + 0x24, i, 1);
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(object + 0x22) = 4;
    arg0 = (void*)fn_80048650();
    fn_801F5A04(object + 0x6C, *(s16*)(descriptor + 4),
                fn_80048640(), (u32)arg0);
}
