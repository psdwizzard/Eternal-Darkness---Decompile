typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 lbl_8064D52C;
extern volatile u32 lbl_8064D530;
extern u32 OSDisableInterrupts(void);

void fn_801CE250(void)
{
    lbl_8064D530 = OSDisableInterrupts();
    lbl_8064D52C = 1;
}
