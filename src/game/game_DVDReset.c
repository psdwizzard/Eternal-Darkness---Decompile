typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

extern void DVDLowReset(void);
extern BOOL ResetRequired_8064DA38;
extern s32 ResumeFromHere_8064DA28;

volatile u32 __DIRegs[16] : 0xCC006000;

void DVDReset(void) {
    DVDLowReset();
    __DIRegs[0] = 0x2A;
    __DIRegs[1] = __DIRegs[1];
    ResetRequired_8064DA38 = 0;
    ResumeFromHere_8064DA28 = 0;
}
