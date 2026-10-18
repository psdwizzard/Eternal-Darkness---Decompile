/* __DVDPrepareResetAsync: __DVDPrepareResetAsync (Dolphin SDK dvd.c), with DVDPause,
 * DVDCancelAllAsync and DVDResume inlined. */
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
    u8 pad[0x08];
    s32 command;
    s32 state;
    u8 pad10[0x18];
    DVDCBCallback callback;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void __DVDClearWaitingQueue(void);
extern DVDCommandBlock *__DVDPopWaitingQueue(void);
extern BOOL DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback callback);
extern void stateReady_80214A10(void);

extern DVDCommandBlock *executing_8064DA00;
extern volatile s32 PauseFlag_8064DA0C;
extern volatile s32 PausingFlag_8064DA10;
extern u32 Canceling;
extern DVDCBCallback CancelCallback;

static inline void DVDPause(void) {
    BOOL level = OSDisableInterrupts();
    PauseFlag_8064DA0C = 1;
    if (executing_8064DA00 == 0)
        PausingFlag_8064DA10 = 1;
    OSRestoreInterrupts(level);
}

static inline void DVDResume(void) {
    BOOL level = OSDisableInterrupts();
    PauseFlag_8064DA0C = 0;
    if (PausingFlag_8064DA10) {
        PausingFlag_8064DA10 = 0;
        stateReady_80214A10();
    }
    OSRestoreInterrupts(level);
}

static inline BOOL DVDCancelAllAsync(DVDCBCallback callback) {
    BOOL enabled;
    DVDCommandBlock *p;
    BOOL retVal;

    enabled = OSDisableInterrupts();
    DVDPause();

    while ((p = __DVDPopWaitingQueue()) != 0) {
        DVDCancelAsync(p, 0);
    }

    if (executing_8064DA00) {
        retVal = DVDCancelAsync(executing_8064DA00, callback);
    } else {
        retVal = 1;
        if (callback) {
            (*callback)(0, 0);
        }
    }

    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

void __DVDPrepareResetAsync(DVDCBCallback callback) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    __DVDClearWaitingQueue();
    if (Canceling) {
        CancelCallback = callback;
    } else {
        if (executing_8064DA00) {
            executing_8064DA00->callback = 0;
        }
        DVDCancelAllAsync(callback);
    }
    OSRestoreInterrupts(enabled);
}
