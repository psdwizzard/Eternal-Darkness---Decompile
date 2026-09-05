extern int lbl_805FAAD8[1537];
extern int lbl_8064D1B8;
extern int lbl_8064D1D8;

extern void fn_801E7DC8(int);

void fn_8016B914(int checkpoint)
{
    int total = 0;
    int i;

    for (i = 0; i < 1536; i++) {
        total += __abs(lbl_805FAAD8[i]);
    }

    if (checkpoint == -1) {
        fn_801E7DC8(0x112);
        fn_801E7DC8(0x100);
        lbl_8064D1D8 = lbl_8064D1B8;
    }
    if (checkpoint == -2) {
        fn_801E7DC8(0x112);
        fn_801E7DC8(0x100);
        lbl_8064D1D8 = lbl_8064D1B8;
    }
}
