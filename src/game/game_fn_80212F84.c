typedef signed int s32;

extern volatile s32 StopAtNextInt_8064D998;
extern s32 lbl_8064D9B8;

s32 fn_80212F84(void) {
    StopAtNextInt_8064D998 = 1;
    lbl_8064D9B8 = 1;
    return 1;
}
