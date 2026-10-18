typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef int DSError;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;

typedef struct TRKStepStatus {
    BOOL active;
    u8 type;
    u32 count;
    u32 rangeStart;
    u32 rangeEnd;
} TRKStepStatus;

extern u8 gTRKCPUState[];
extern u8 gTRKState[];
extern TRKStepStatus gTRKStepStatus;
extern DSError TRKDoNotifyStopped(u8 command);

static inline void TRKTargetEnableTrace(BOOL enable)
{
    if (enable) {
        *(u32 *)(gTRKCPUState + 0x1F8) |= 0x400;
    } else {
        *(u32 *)(gTRKCPUState + 0x1F8) &= ~0x400U;
    }
}

static inline void TRKTargetSetStopped(BOOL stopped)
{
    *(u32 *)(gTRKState + 0x98) = stopped;
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

static inline BOOL TRKTargetCheckStep(void)
{
    BOOL done = 1;

    TRKTargetEnableTrace(0);
    if (gTRKStepStatus.active &&
        (*(u32 *)(gTRKCPUState + 0x2F8) & 0xFFFF) == 0xD00) {
        switch (gTRKStepStatus.type) {
        case 0:
            if (gTRKStepStatus.count != 0) {
                done = 0;
            }
            break;
        case 1:
            if (*(u32 *)(gTRKCPUState + 0x80) >= gTRKStepStatus.rangeStart &&
                *(u32 *)(gTRKCPUState + 0x80) <= gTRKStepStatus.rangeEnd) {
                done = 0;
            }
            break;
        }
    }
    return done;
}

DSError TRKTargetInterrupt(TRKEvent *event)
{
    DSError error = 0;

    switch (event->type) {
    case 3:
    case 4:
        if (gTRKStepStatus.active) {
            if (TRKTargetCheckStep()) {
                gTRKStepStatus.active = 0;
            } else {
                TRKTargetDoStep();
            }
        }
        if (!gTRKStepStatus.active) {
            TRKTargetSetStopped(1);
            error = TRKDoNotifyStopped(0x90);
        }
        break;
    }
    return error;
}
