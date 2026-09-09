typedef float Matrix34[3][4];

extern float lbl_80651348;
extern float lbl_8065137C;
extern float lbl_80651378;
extern float lbl_806513E4;
extern float lbl_806513FC;
extern float lbl_80651400;

extern void fn_802119B0();
extern void fn_8022B4B8();
extern void fn_80210FB0();
extern void fn_80211484();
extern void fn_8022B690();
extern void fn_801ED468();
extern void fn_80226D28();

void fn_801F44DC(void)
{
    float projection[18];
    Matrix34 matrix;
    float one = lbl_80651348;

    fn_802119B0(projection, one, lbl_8065137C,
                one, lbl_80651378, one,
                lbl_806513E4);
    fn_8022B4B8(projection, 1);
    fn_80210FB0(matrix);
    fn_80211484(matrix, lbl_806513FC, lbl_80651400, lbl_80651348);
    fn_8022B690(matrix, 0);
    fn_801ED468(0);
    fn_80226D28(0);
}
