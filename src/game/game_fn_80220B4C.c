typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;
typedef signed long long OSTime;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, OSContext *context);
typedef void (*EXICallback)(s32 channel, void *context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTime period;
    OSTime start;
};

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 reserved08[0x24 - 0x08];
    s32 mountStep;
    u8 reserved28[0xE0 - 0x28];
    OSAlarm alarm;
    u8 reserved108[8];
} CARDControl;

extern CARDControl __CARDBlock[];
extern s32 __CARDGetControlBlock(s32 channel, CARDControl **outCard);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
extern BOOL EXIDetach(s32 channel);
extern void OSCancelAlarm(OSAlarm *alarm);

/* Release the card's EXI connection while interrupts are disabled. */
static s32 Unmount(s32 channel)
{
    BOOL enabled;
    CARDControl *card;

    card = &__CARDBlock[channel];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(channel, 0);
        EXIDetach(channel);
        OSCancelAlarm(&card->alarm);
        card->attached = 0;
        card->result = -3;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

s32 CARDUnmount(s32 channel)
{
    CARDControl *control;
    s32 result;

    result = __CARDGetControlBlock(channel, &control);
    if (result < 0) {
        return result;
    }
    return Unmount(channel);
}
