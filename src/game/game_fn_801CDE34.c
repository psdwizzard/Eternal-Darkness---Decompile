typedef unsigned int u32;
typedef unsigned char u8;

extern void* lbl_8064D514;
extern volatile u32 lbl_8064D518;
extern u32 lbl_8064D51C;
extern u32 lbl_8064D520;
extern volatile u32 lbl_8064D524;
extern void (*lbl_8064D510)(void);
extern u8 lbl_8064D534;

extern void fn_8021A088(void*, u32);
extern u32 OSGetTick(void);
extern void OSEnableInterrupts(void);
extern void OSDisableInterrupts(void);

void fn_801CDE34(void)
{
    char* base;

    lbl_8064D534 = (lbl_8064D534 + 1) % 4;
    base = (char*)lbl_8064D514 + 0x80000000;
    fn_8021A088(base + lbl_8064D534 * 640, 640);
    lbl_8064D524 = OSGetTick();
    if (lbl_8064D518 != 0) {
        if (lbl_8064D520 == 0) {
            lbl_8064D520 = 1;
            OSEnableInterrupts();
            lbl_8064D510();
            OSDisableInterrupts();
            lbl_8064D520 = 0;
        }
    } else {
        lbl_8064D51C = 1;
    }
}
