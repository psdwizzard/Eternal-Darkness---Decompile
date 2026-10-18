typedef unsigned char u8;
typedef unsigned int u32;

extern u8 lbl_8064C368;
extern u32 lbl_8064D5E8;
extern float lbl_8064DF38;
extern char lbl_806391F0[];

extern void PERFStartFrame(void);
extern void PERFStartAutoSampling(float);
extern void OSStartStopwatch(void*);

void fn_800243E8(void)
{
    if (lbl_8064C368 == 0 && (lbl_8064D5E8 & 1) == 0) {
        PERFStartFrame();
        PERFStartAutoSampling(lbl_8064DF38);
    }
    OSStartStopwatch(lbl_806391F0);
}
