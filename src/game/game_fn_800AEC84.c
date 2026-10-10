typedef unsigned int u32;
typedef signed short s16;

extern void fn_801A8D38(int);
extern void fn_801E3AA4(int);
extern void fn_801E5430(s16, s16);
extern u32 fn_801E3A34(u32*);
extern void fn_801E56AC(float, const char*, ...);

extern char lbl_8064B6A8;
extern const u32 lbl_8064EFF8;
extern const float lbl_8064EFFC;

void fn_800AEC84(void)
{
    u32 textColor;

    fn_801A8D38(5);
    fn_801E3AA4(0);
    fn_801E5430(0x1C7, 0x1F);
    textColor = lbl_8064EFF8;
    fn_801E3A34(&textColor);
    fn_801E56AC(lbl_8064EFFC, &lbl_8064B6A8);
}
