typedef unsigned int u32;
typedef unsigned char u8;
typedef int BOOL;
typedef int DSError;

typedef struct TRKStepStatus {
    BOOL active;
    u8 type;
    u32 count;
    u32 rangeStart;
    u32 rangeEnd;
} TRKStepStatus;

extern u8 gTRKCPUState[];
extern u8 gTRKState[];
extern TRKStepStatus lbl_8024A874;
#define gTRKStepStatus lbl_8024A874

static inline void TRKTargetEnableTrace(BOOL enable)
{
    if (enable) {
        *(u32*)(gTRKCPUState + 0x1F8) |= 0x400;
    } else {
        *(u32*)(gTRKCPUState + 0x1F8) &= ~0x400;
    }
}

static inline void TRKTargetSetStopped(BOOL stopped)
{
    *(u32*)(gTRKState + 0x98) = stopped;
}

static inline DSError TRKTargetDoStep(void)
{
    gTRKStepStatus.active = 1;
    TRKTargetEnableTrace(1);

    if (gTRKStepStatus.type == 0 || gTRKStepStatus.type == 0x10) {
        gTRKStepStatus.count--;
    }

    TRKTargetSetStopped(0);
    return 0;
}

DSError fn_800F3EEC(u32 rangeStart, u32 rangeEnd, BOOL stepOver)
{
    DSError error = 0;

    if (stepOver) {
        error = 0x703;
    } else {
        gTRKStepStatus.type = 1;
        gTRKStepStatus.rangeStart = rangeStart;
        gTRKStepStatus.rangeEnd = rangeEnd;
        error = TRKTargetDoStep();
    }

    return error;
}
