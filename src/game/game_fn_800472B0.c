typedef int s32;

extern struct {
    char pad0[0xC];
    s32 unkC;
    s32 unk10;
} lbl_80265FD8;
extern s32 lbl_8064C80C;
extern s32 lbl_8064C810;

void fn_800472B0(s32 arg0) {
    if (arg0 == 0) {
        lbl_80265FD8.unkC = 0x80;
        lbl_80265FD8.unk10 = 0x80;
        lbl_8064C810 = 0;
        return;
    }
    lbl_80265FD8.unkC = 0x7C;
    lbl_80265FD8.unk10 = 0x84;
    lbl_8064C810 = 1;
    lbl_8064C80C = 2;
}
