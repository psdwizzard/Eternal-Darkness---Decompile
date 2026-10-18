/* DVDCancelAsync: DVDCancelAsync (Dolphin SDK dvd.c) */
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
extern BOOL DVDLowBreak(void);
extern DVDLowCallback DVDLowClearCallback(void);
extern BOOL __DVDDequeueWaitingQueue(DVDCommandBlock *block);
extern void cbForStateMotorStopped_8021492C(u32 intType);
extern void stateReady_80214A10(void);

extern u32 Canceling;
extern DVDCBCallback CancelCallback;
extern s32 ResumeFromHere_8064DA28;

BOOL DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback callback) {
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
        if (Canceling) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        Canceling = 1;
        CancelCallback = callback;
        if ((u32)block->command == 4 || (u32)block->command == 1)
            DVDLowBreak();
        break;

    case 2:
        __DVDDequeueWaitingQueue(block);
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
            if (Canceling) {
                OSRestoreInterrupts(enabled);
                return 0;
            }
            Canceling = 1;
            CancelCallback = callback;
            break;
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        old = DVDLowClearCallback();
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
