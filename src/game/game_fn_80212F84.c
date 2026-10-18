typedef signed int s32;

extern volatile s32 StopAtNextInt_8064D998;
extern s32 Breaking;

s32 DVDLowBreak(void) {
    StopAtNextInt_8064D998 = 1;
    Breaking = 1;
    return 1;
}
