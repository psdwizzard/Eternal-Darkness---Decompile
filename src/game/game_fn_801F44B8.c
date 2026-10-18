typedef signed long s32;

extern s32 lbl_8064D740;
extern void GXSetDispCopyGamma(void);

void fn_801F44B8(s32 value)
{
    lbl_8064D740 = value;
    GXSetDispCopyGamma();
}
