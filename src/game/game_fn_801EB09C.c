typedef unsigned int u32;

extern char lbl_806391F0[];
extern char lbl_8063BEC0[];
extern double lbl_80651308;
extern float lbl_8064D5D8;

extern void OSCheckStopwatch(void*);
extern float fn_800F6264(void);
extern void OSReceiveMessage(void*, int, int);

void fn_801EB09C(void)
{
    float elapsed;
    u32 ticks;

    OSCheckStopwatch(lbl_806391F0);
    elapsed = fn_800F6264();
    ticks = (*(volatile u32*)0x800000F8 >> 2) / 1000;
    lbl_8064D5D8 = elapsed / (float)ticks;
    OSReceiveMessage(lbl_8063BEC0, 0, 1);
}
