/* fn_80215D3C: DVDCancelAsync (Dolphin SDK dvd.c) */
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);
typedef void (*DVDLowCallback)(u32 intType);

struct DVDCommandBlock {
    u8 pad[0x08];
    s32 command;
    s32 state;
    u8 pad10[0x18];
    DVDCBCallback callback;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern BOOL fn_80212F84(void);
extern DVDLowCallback fn_80212F98(void);
extern BOOL fn_80216580(DVDCommandBlock *block);
extern void cbForStateMotorStopped_8021492C(u32 intType);
extern void stateReady_80214A10(void);

extern u32 lbl_8064DA20;
extern DVDCBCallback lbl_8064DA24;
extern s32 ResumeFromHere_8064DA28;

BOOL fn_80215D3C(DVDCommandBlock *block, DVDCBCallback callback) {
    BOOL enabled;
    DVDLowCallback old;

    enabled = OSDisableInterrupts();

    switch (block->state) {
    case -1:
    case 0:
    case 10:
        if (callback)
            (*callback)(0, block);
        break;

    case 1:
        if (lbl_8064DA20) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        lbl_8064DA20 = 1;
        lbl_8064DA24 = callback;
        if ((u32)block->command == 4 || (u32)block->command == 1)
            fn_80212F84();
        break;

    case 2:
        fn_80216580(block);
        block->state = 10;
        if (block->callback)
            (block->callback)(-3, block);
        if (callback)
            (*callback)(0, block);
        break;

    case 3:
        switch (block->command) {
        case 5:
        case 4:
        case 13:
        case 15:
            if (callback)
                (*callback)(0, block);
            break;
        default:
            if (lbl_8064DA20) {
                OSRestoreInterrupts(enabled);
                return 0;
            }
            lbl_8064DA20 = 1;
            lbl_8064DA24 = callback;
            break;
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        old = fn_80212F98();
        if (old != cbForStateMotorStopped_8021492C) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        if (block->state == 4)
            ResumeFromHere_8064DA28 = 3;
        if (block->state == 5)
            ResumeFromHere_8064DA28 = 4;
        if (block->state == 6)
            ResumeFromHere_8064DA28 = 1;
        if (block->state == 11)
            ResumeFromHere_8064DA28 = 2;
        if (block->state == 7)
            ResumeFromHere_8064DA28 = 7;
        block->state = 10;
        if (block->callback)
            (block->callback)(-3, block);
        if (callback)
            (*callback)(0, block);
        stateReady_80214A10();
        break;
    }

    OSRestoreInterrupts(enabled);
    return 1;
}
