typedef unsigned long u32;

extern u32 lbl_8064D70C;
extern u32 lbl_8064D72C;
extern u32 lbl_8064D730;
extern u32 lbl_8064D708;
extern u32 lbl_8064D5E4;

extern u32 OSGetTick(void);

void fn_801F3EDC(void)
{
    u32 rate;

    lbl_8064D72C = (OSGetTick() - lbl_8064D70C) /
                   ((*(u32*)0x800000F8 / 4) / 1000);
    lbl_8064D730 = OSGetTick() - lbl_8064D730;
    lbl_8064D708++;
    lbl_8064D730 = OSGetTick();
    if (lbl_8064D72C > 1000) {
        rate = (lbl_8064D708 * 1000) / lbl_8064D72C;
        lbl_8064D70C = OSGetTick();
        lbl_8064D708 = 0;
        if (rate != 0) {
            lbl_8064D5E4 = rate;
        }
    }
}
