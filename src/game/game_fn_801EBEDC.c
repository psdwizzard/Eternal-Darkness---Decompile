typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 lbl_80639260[];
extern u8 lbl_80265D80[];
extern float lbl_80651318;

extern void* lbl_8064D604;
extern void* lbl_8064D608;
extern void* lbl_8064D60C;
extern void* lbl_8064D610;
extern void* lbl_8064D614;
extern void* lbl_8064D600;
extern void* lbl_8064D688;
extern void* lbl_8064D68C[2];

extern u32 fn_80228250(u16, u16, u32, u8, u8);
extern void* fn_801FEA8C(u32, u32, const char*, u32);
extern void fn_802286E8(void*, void*, u16, u16, u32, u32, u32, u8, u32);
extern void fn_80228730(void*, u32, u32, float, float, float, u8, u8, u8);
extern void fn_80228B50(void*, void*, u32, u16);
extern void fn_801EBC6C(void*, void*, void*);
extern void DCFlushRange(void*, u32);
extern void fn_80228474(void*, void*, u16, u16, u32, u32, u32, u8);

#pragma opt_common_subs off
void fn_801EBEDC(void)
{
    u8* data = lbl_80265D80;
    u8* bss = lbl_80639260;
    register void* image;
    register void* texture = bss + 0x2000;
    int value;
    u32 size;
    u16* out;
    int i;

    if (lbl_8064D604 == 0 && lbl_8064D688 == 0) {
        size = fn_80228250(0x100, 0x100, 1, 0, 0);
        image = fn_801FEA8C(size, 1, (char*)data + 0x490, 745);
        lbl_8064D68C[0] = image;
        lbl_8064D68C[1] = image;
        fn_802286E8(texture, image, 0x100, 0x100, 9, 1, 1, 0, 0);
        fn_80228730(texture, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);

        lbl_8064D604 = fn_801FEA8C(0x200, 1, (char*)data + 0x490, 754);
        lbl_8064D608 = fn_801FEA8C(0x200, 1, (char*)data + 0x490, 755);
        lbl_8064D60C = fn_801FEA8C(0x200, 1, (char*)data + 0x490, 756);
        lbl_8064D610 = fn_801FEA8C(0x200, 1, (char*)data + 0x490, 757);
        lbl_8064D614 = fn_801FEA8C(0x200, 1, (char*)data + 0x490, 758);
        lbl_8064D688 = image;

        fn_80228B50(bss + 0x2040, lbl_8064D604, 0, 0x100);
        fn_80228B50(bss + 0x204C, lbl_8064D608, 0, 0x100);
        fn_80228B50(bss + 0x2058, lbl_8064D60C, 0, 0x100);
        fn_80228B50(bss + 0x2064, lbl_8064D610, 0, 0x100);
        fn_80228B50(bss + 0x2070, lbl_8064D614, 0, 0x100);

        fn_802286E8(bss + 0x207C, image, 0x100, 0x100, 9, 1, 1, 0, 2);
        fn_80228730(bss + 0x207C, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);
        fn_802286E8(bss + 0x209C, image, 0x100, 0x100, 9, 1, 1, 0, 3);
        fn_80228730(bss + 0x209C, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);
        fn_802286E8(bss + 0x20BC, image, 0x100, 0x100, 9, 1, 1, 0, 4);
        fn_80228730(bss + 0x20BC, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);
        fn_802286E8(bss + 0x20DC, image, 0x100, 0x100, 9, 1, 1, 0, 5);
        fn_80228730(bss + 0x20DC, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);

        fn_801EBC6C(data + 0x258, bss + 0x20FC, lbl_8064D610);
        fn_801EBC6C(data + 0x20, bss + 0x2114, lbl_8064D608);
        fn_801EBC6C(data + 0x13C, bss + 0x212C, lbl_8064D60C);
        fn_801EBC6C(data + 0x374, bss + 0x2144, lbl_8064D614);
    }

    if (lbl_8064D600 == 0) {
        u16* base;
        value = 0xFF;
        size = fn_80228250(0x100, 1, 3, 0, 0);
        lbl_8064D600 = fn_801FEA8C(size, 1, (char*)data + 0x490, 797);
        base = lbl_8064D600;
        out = base;
        for (i = 0x101; i != 0; i--) {
            *out = value;
            if (--value < 0)
                value = 0;
            out++;
        }
        *base = 0xFFFF;
        DCFlushRange(base, size);
        fn_80228474(bss + 0x215C, lbl_8064D600, 0x100, 1, 3, 0, 0, 0);
        fn_80228730(bss + 0x215C, 1, 1, lbl_80651318, lbl_80651318,
                   lbl_80651318, 0, 0, 0);
    }
}
#pragma opt_common_subs reset
