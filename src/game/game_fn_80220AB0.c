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
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
extern BOOL EXIDetach(s32 channel);
extern void OSCancelAlarm(OSAlarm *alarm);

/* Detach the card's EXI connection and record the result (DoUnmount). */
void DoUnmount(s32 channel, s32 result)
{
    CARDControl *card;
    BOOL enabled;

    card = &__CARDBlock[channel];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(channel, 0);
        EXIDetach(channel);
        OSCancelAlarm(&card->alarm);
        card->attached = 0;
        card->result = result;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
}
