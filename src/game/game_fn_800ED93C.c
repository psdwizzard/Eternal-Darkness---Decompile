extern const float lbl_8064F8F8;
extern const float lbl_8064F8FC;
extern const float lbl_8064F900;
extern const float lbl_8064F904;

extern void fn_800243E8();
extern void fn_801EF530();
extern void fn_80225FD8();
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_800ED7AC(void *);
extern void fn_800ED870();

void fn_800ED93C(void) {
    char buf[0x38];

    fn_800243E8();
    fn_801EF530();
    fn_80225FD8();
    fn_8022B94C(lbl_8064F8F8, lbl_8064F8F8, lbl_8064F8FC, lbl_8064F900, lbl_8064F8F8, lbl_8064F904);
    fn_800ED7AC(buf);
    fn_800ED870();
}
