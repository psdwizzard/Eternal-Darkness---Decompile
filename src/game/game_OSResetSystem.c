/* OSResetSystem (0x8020DEF4, 632 bytes)
 * Dolphin SDK OSReset.c: OSResetSystem with CallResetFunctions and
 * KillThreads inlined. */

typedef int BOOL;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef BOOL (*OSResetFunction)(BOOL final);

typedef struct OSResetFunctionInfo {
    OSResetFunction func;
    u32 priority;
    struct OSResetFunctionInfo *next;
    struct OSResetFunctionInfo *prev;
} OSResetFunctionInfo;

typedef struct OSThread {
    u8 context[0x2C8];
    u16 state;
    u16 attr;
    u8 pad2CC[0x2FC - 0x2CC];
    struct OSThread *nextActive;
    struct OSThread *prevActive;
} OSThread;

typedef struct OSSram {
    u8 pad[0x13];
    u8 flags;
} OSSram;

extern OSResetFunctionInfo *ResetFunctionQueue_8064D960;

extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern void __OSStopAudioSystem(void);
extern BOOL __PADDisableRecalibration(BOOL disable);
extern BOOL __OSSyncSram(void);
extern OSSram *__OSLockSram(void);
extern BOOL __OSUnlockSram(BOOL commit);
extern BOOL OSDisableInterrupts(void);
extern void LCDisable(void);
extern void ICFlashInvalidate(void);
extern void Reset_8020DE3C(u32 resetCode);
extern void OSCancelThread(OSThread *thread);
extern void __OSReboot(u32 resetCode, BOOL forceMenu);
extern void *memset(void *dst, int c, unsigned long n);

#define __OSActiveThreadQueueHead (*(OSThread **)0x800000DC)
#define __VIRegs ((volatile u16 *)0xCC002000)

static inline BOOL CallResetFunctions(BOOL final) {
    OSResetFunctionInfo *info;
    BOOL err = 0;

    for (info = ResetFunctionQueue_8064D960; info != 0; info = info->next) {
        err |= !info->func(final);
    }
    err |= !__OSSyncSram();
    if (err) {
        return 0;
    }
    return 1;
}

static inline void KillThreads(void) {
    OSThread *thread;
    OSThread *next;

    for (thread = __OSActiveThreadQueueHead; thread != 0; thread = next) {
        next = thread->nextActive;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
            break;
        }
    }
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
    BOOL disableRecalibration;

    OSDisableScheduler();
    __OSStopAudioSystem();
    if (reset == 2) {
        disableRecalibration = __PADDisableRecalibration(1);
    }

    while (!CallResetFunctions(0)) {
    }

    if (reset == 1 && forceMenu) {
        OSSram *sram;

        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(1);
        while (!__OSSyncSram()) {
        }
    }

    OSDisableInterrupts();
    CallResetFunctions(1);
    LCDisable();

    if (reset == 1) {
        OSDisableInterrupts();
        __VIRegs[1] = 0;
        ICFlashInvalidate();
        Reset_8020DE3C(resetCode * 8);
    } else if (reset == 0) {
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    KillThreads();
    memset((void *)0x80000040, 0, 0x8C);
    memset((void *)0x800000D4, 0, 0x14);
    memset((void *)0x800000F4, 0, 4);
    memset((void *)0x80003000, 0, 0xC0);
    memset((void *)0x800030C8, 0, 0xC);
    memset((void *)0x800030E2, 0, 1);
    __PADDisableRecalibration(disableRecalibration);
}
