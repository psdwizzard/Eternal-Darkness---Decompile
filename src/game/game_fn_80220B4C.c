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

extern CARDControl lbl_80641C60[];
extern s32 fn_8021D2BC(s32 channel, CARDControl **outCard);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern EXICallback fn_80206ED4(s32 channel, EXICallback callback);
extern BOOL fn_80207304(s32 channel);
extern void fn_8020A93C(OSAlarm *alarm);

/* Release the card's EXI connection while interrupts are disabled. */
static s32 Unmount(s32 channel)
{
    BOOL enabled;
    CARDControl *card;

    card = &lbl_80641C60[channel];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        fn_80206ED4(channel, 0);
        fn_80207304(channel);
        fn_8020A93C(&card->alarm);
        card->attached = 0;
        card->result = -3;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

s32 fn_80220B4C(s32 channel)
{
    CARDControl *control;
    s32 result;

    result = fn_8021D2BC(channel, &control);
    if (result < 0) {
        return result;
    }
    return Unmount(channel);
}
