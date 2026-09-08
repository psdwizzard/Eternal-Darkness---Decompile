typedef unsigned char u8;
typedef unsigned int u32;

extern char lbl_806391F0[];
extern double lbl_80651308;
extern float lbl_8064D5DC;
extern volatile u8 lbl_8064C368;

extern void fn_8020F088(void*);
extern float fn_800F6264(void);

void fn_801EB11C(void)
{
    float elapsed;
    u32 ticks;

    fn_8020F088(lbl_806391F0);
    elapsed = fn_800F6264();
    ticks = (*(volatile u32*)0x800000F8 >> 2) / 1000;
    lbl_8064D5DC = elapsed / (float)ticks;
    if (lbl_8064C368 != 2) {
        (void)lbl_8064C368;
    }
}
