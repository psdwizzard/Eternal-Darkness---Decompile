typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef s64 OSTime;

typedef struct OSContext {
    double align;
    char data[0x2C0];
} OSContext;

typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDCommand {
    s32 cmd;
    void *addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

typedef struct DVDLowReadRegion {
    void *addr;
    u32 length;
    u32 offset;
} DVDLowReadRegion;

/* dvdlow.c static work area: command list, timeout alarm, last/current read */
typedef struct DVDLowWork {
    DVDCommand cmdList[5];
    char pad_64[0x4];
    char alarm[0x50];
    DVDLowReadRegion prev;
    DVDLowReadRegion curr;
} DVDLowWork;

extern DVDLowWork CommandList_80641880;
extern volatile s32 NextCommandNumber_8064D9DC;
extern volatile s32 LastCommandWasRead;
/* LastReadFinished; symbols.txt splits it into two 4-byte labels (C8/CC) */
extern OSTime LastReadFinished;
extern s32 FirstRead;
extern volatile s32 StopAtNextInt_8064D998;
extern volatile u32 ResetOccurred_8064D9B0;
extern volatile OSTime LastResetEnd_8064D9A8;
extern s32 WaitingCoverClose_8064D9B4;
extern s32 Breaking;
extern DVDLowCallback Callback_8064D9A0;
extern DVDLowCallback ResetCoverCallback;

extern void OSCancelAlarm(void *alarm);
extern OSTime __OSGetSystemTime(void);
extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern s32 Read(void *addr, u32 length, u32 offset, DVDLowCallback callback);
extern s32 DVDLowSeek(u32 offset, DVDLowCallback callback);

volatile u32 __DIRegs[16] : 0xCC006000;

static inline s32 ProcessNextCommand(DVDLowWork *w) {
    s32 n = NextCommandNumber_8064D9DC;

    if (w->cmdList[n].cmd == 1) {
        NextCommandNumber_8064D9DC++;
        Read(w->cmdList[n].addr, w->cmdList[n].length, w->cmdList[n].offset, w->cmdList[n].callback);
        return 1;
    } else if (w->cmdList[n].cmd == 2) {
        NextCommandNumber_8064D9DC++;
        DVDLowSeek(w->cmdList[n].offset, w->cmdList[n].callback);
        return 1;
    }
    return 0;
}

void __DVDInterruptHandler(s32 interrupt, OSContext *context) {
    DVDLowCallback cb;
    OSContext exceptionContext;
    u32 cause = 0;
    u32 reg;
    u32 intr;
    u32 mask;
    DVDLowWork *w = &CommandList_80641880;

    OSCancelAlarm(w->alarm);

    if (LastCommandWasRead) {
        LastReadFinished = __OSGetSystemTime();
        FirstRead = 0;
        w->prev.addr = w->curr.addr;
        w->prev.length = w->curr.length;
        w->prev.offset = w->curr.offset;
        if (StopAtNextInt_8064D998 == 1) {
            cause |= 8;
        }
    }

    LastCommandWasRead = 0;
    StopAtNextInt_8064D998 = 0;

    reg = __DIRegs[0];
    mask = reg & 0x2a;
    intr = (reg & 0x54) & (mask << 1);

    if (intr & 0x40) {
        cause |= 8;
    }
    if (intr & 0x10) {
        cause |= 1;
    }
    if (intr & 4) {
        cause |= 2;
    }

    if (cause) {
        ResetOccurred_8064D9B0 = 0;
    }

    __DIRegs[0] = intr | mask;

    if (ResetOccurred_8064D9B0 &&
        (__OSGetSystemTime() - LastResetEnd_8064D9A8) < ((*(u32 *)0x800000F8 / 4) / 1000) * 200) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            if (ResetCoverCallback) {
                ResetCoverCallback(4);
            }
            ResetCoverCallback = 0;
        }
        __DIRegs[1] = __DIRegs[1];
    } else if (WaitingCoverClose_8064D9B4) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            cause |= 4;
        }
        __DIRegs[1] = intr | mask;
        WaitingCoverClose_8064D9B4 = 0;
    } else {
        __DIRegs[1] = 0;
    }

    if ((cause & 8) && !Breaking) {
        cause &= ~8;
    }

    if (cause & 1) {
        if (ProcessNextCommand(w)) {
            return;
        }
    } else {
        w->cmdList[0].cmd = -1;
        NextCommandNumber_8064D9DC = 0;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (cause) {
        cb = Callback_8064D9A0;
        Callback_8064D9A0 = 0;
        if (cb) {
            cb(cause);
        }
        Breaking = 0;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
