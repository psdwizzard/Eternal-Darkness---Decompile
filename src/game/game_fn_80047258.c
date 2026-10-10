extern int lbl_80265FD8[];
extern void fn_80047248();

void fn_80047258(int mode) {
    if (mode != 0) {
        lbl_80265FD8[3] = 0x7C;
        lbl_80265FD8[4] = 0x84;
    } else {
        lbl_80265FD8[3] = 0x80;
        lbl_80265FD8[4] = 0x80;
        fn_80047248();
    }
}
