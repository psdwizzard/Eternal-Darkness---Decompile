/* fn_802161E8: DVDCheckDisk (Dolphin SDK dvd.c), with DVDGetDriveStatus
 * inlined. */
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
} DVDCommandBlock;

volatile u32 __DIRegs[16] : 0xCC006000;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

extern DVDCommandBlock *executing_8064DA00;
extern DVDCommandBlock DummyCommandBlock_806419E0;
extern volatile s32 PausingFlag_8064DA10;
extern s32 FatalErrorFlag_8064DA18;

BOOL fn_802161E8(void) {
    BOOL enabled;
    BOOL retVal;
    s32 state;
    u32 coverReg;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag_8064DA18) {
        state = -1;
    } else if (PausingFlag_8064DA10) {
        state = 8;
    } else if (executing_8064DA00 == 0) {
        state = 0;
    } else if (executing_8064DA00 == &DummyCommandBlock_806419E0) {
        state = 0;
    } else {
        state = executing_8064DA00->state;
    }

    switch (state) {
    case 1:
    case 9:
    case 10:
    case 2:
        retVal = 1;
        break;
    case -1:
    case 11:
    case 7:
    case 3:
    case 4:
    case 5:
    case 6:
        retVal = 0;
        break;
    case 0:
    case 8:
        coverReg = __DIRegs[1];
        if (((coverReg >> 2) & 1) || (coverReg & 1)) {
            retVal = 0;
        } else {
            retVal = 1;
        }
        break;
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}
