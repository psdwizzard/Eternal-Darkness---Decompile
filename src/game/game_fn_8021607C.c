/* fn_8021607C: DVDCancelAll (Dolphin SDK dvd.c), with DVDCancelAllAsync,
 * DVDPause and DVDResume inlined. */
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern DVDCommandBlock *__DVDPopWaitingQueue(void);
extern BOOL fn_80215D3C(DVDCommandBlock *block, DVDCBCallback callback);
extern void fn_80210004(OSThreadQueue *queue);
extern void stateReady_80214A10(void);
extern void fn_802161B4(s32 result, DVDCommandBlock *block);

extern DVDCommandBlock *executing_8064DA00;
extern volatile s32 PauseFlag_8064DA0C;
extern volatile s32 PausingFlag_8064DA10;
extern BOOL lbl_8064DA3C;
extern OSThreadQueue __DVDThreadQueue;

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
    while ((p = __DVDPopWaitingQueue()) != 0)
        fn_80215D3C(p, 0);

    if (executing_8064DA00) {
        retVal = fn_80215D3C(executing_8064DA00, callback);
    } else {
        retVal = 1;
        if (callback)
            (*callback)(0, 0);
    }
    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

s32 fn_8021607C(void) {
    BOOL result;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    lbl_8064DA3C = 0;

    result = DVDCancelAllAsync(fn_802161B4);
    if (result == 0) {
        OSRestoreInterrupts(enabled);
        return -1;
    }

    for (;;) {
        if (lbl_8064DA3C)
            break;
        fn_80210004(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}
