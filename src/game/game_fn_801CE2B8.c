typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 lbl_8064D52C;
extern volatile u32 lbl_8064D530;
extern u32 OSDisableInterrupts(void);

void fn_801CE2B8(void)
{
    u16 count = lbl_8064D52C;
    lbl_8064D52C = count + 1;
    if (count == 0) {
        lbl_8064D530 = OSDisableInterrupts();
    }
}
