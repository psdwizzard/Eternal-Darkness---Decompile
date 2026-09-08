typedef unsigned int u32;

extern int lbl_8064D6A4;
extern int lbl_8064D6A8;
extern volatile u32* lbl_8064D68C;

extern void* fn_8012072C(u32);
extern void fn_801EF3D0(void);
extern void* memset(void*, int, u32);
extern void fn_801EC318(void*, int, int, int);
extern void fn_801EC350(void*, int, int, int, int);
extern void DCInvalidateRange(void*, u32);
extern volatile u32* fn_80224650(volatile u32*);
extern void fn_80224754(void);

void fn_801EBA58(void* enabled)
{
    u32* image = fn_8012072C(0x10000);
    register u32* p0;
    register u32* base;
    register int row;

    if (enabled != 0 && image != 0) {
        volatile u32* fifo;

        fn_801EF3D0();
        lbl_8064D6A8 = 0xFF;
        lbl_8064D6A4 = 0;
        memset(image, 0, 0x10000);
        fn_801EC318(image, 0, 0, 0x78);
        fn_801EC318(image, 0, 0x100, 0x78);
        fn_801EC318(image, 0x100, 0x100, 0x78);
        fn_801EC318(image, 0x100, 0, 0x78);
        fn_801EC350(image, 0, 0, 0x101, 0x101);
        DCInvalidateRange((void*)lbl_8064D68C, 0x10000);
        fifo = fn_80224650(lbl_8064D68C);

        row = 0;
        base = image;
        do {
            u32* p1 = image + (row + 1) * 0x40;
            u32* p2 = image + (row + 2) * 0x40;
            u32* p3 = image + (row + 3) * 0x40;
            int block;

            p0 = base;

            for (block = 0; block < 0x10; block++) {
                *fifo = p0[0];
                *fifo = p0[1];
                *fifo = p1[0];
                *fifo = p1[1];
                *fifo = p2[0];
                *fifo = p2[1];
                *fifo = p3[0];
                *fifo = p3[1];
                *fifo = p0[2];
                *fifo = p0[3];
                p0 += 4;
                *fifo = p1[2];
                *fifo = p1[3];
                p1 += 4;
                *fifo = p2[2];
                *fifo = p2[3];
                p2 += 4;
                *fifo = p3[2];
                *fifo = p3[3];
                p3 += 4;
            }
            row += 4;
            base += 0x100;
        } while (row < 0x100);
        fn_80224754();
    }
}
