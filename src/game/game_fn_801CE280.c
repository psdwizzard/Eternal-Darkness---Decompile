typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 lbl_8064D52C;
extern volatile u32 lbl_8064D530;
extern void OSRestoreInterrupts(u32);

void fn_801CE280(void)
{
    u16 count = lbl_8064D52C - 1;
    lbl_8064D52C = count;
    if (count == 0) {
        OSRestoreInterrupts(lbl_8064D530);
    }
}
