typedef float Mtx[3][4];

extern Mtx lbl_8063C068;
extern float lbl_80651348;
extern float lbl_8065134C;
extern float lbl_806513A8;
extern float lbl_806513D0;

extern void fn_80210FDC(Mtx, Mtx, Mtx);
extern void fn_802111A0(Mtx, Mtx);
extern void fn_80211484(Mtx, float, float, float);
extern void fn_802114B8(Mtx, float, float, float);
extern void fn_8022B748(Mtx, int, int);

void fn_801F2B44(void)
{
    Mtx temporary;
    Mtx output;

    fn_802111A0(lbl_8063C068, output);
    fn_802114B8(temporary, lbl_806513A8, lbl_806513D0, lbl_80651348);
    fn_80210FDC(temporary, output, output);
    fn_80211484(temporary, lbl_806513A8, lbl_806513A8, lbl_8065134C);
    fn_80210FDC(temporary, output, output);
    fn_8022B748(output, 0x30, 1);
}
