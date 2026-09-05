typedef unsigned int u32;

extern void (*lbl_8064D510)(void);
extern volatile u32 lbl_8064D518;
extern volatile u32 lbl_8064D51C;
extern volatile u32 lbl_8064D520;

extern void OSEnableInterrupts(void);
extern void OSDisableInterrupts(void);

void fn_801CDEE8(void)
{
    volatile u32 padding[2];

    lbl_8064D518 = 1;
    if (lbl_8064D51C != 0) {
        lbl_8064D51C = 0;
        if (lbl_8064D520 == 0) {
            lbl_8064D520 = 1;
            OSEnableInterrupts();
            lbl_8064D510();
            OSDisableInterrupts();
            lbl_8064D520 = 0;
        }
    }
}
