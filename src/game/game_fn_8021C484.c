typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef int BOOL;
typedef signed long long OSTime;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, OSContext *context);
struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTime period;
    OSTime start;
};
typedef void (*EXICallback)(s32 chan, void *context);
typedef void (*CardCallback)(s32 chan, s32 result);

typedef struct CardControl {
    BOOL attached;
    u8 pad04[0xA8 - 4];
    s32 retry;
    u8 padAC[0xCC - 0xAC];
    CardCallback callback;
    u8 padD0[0xE0 - 0xD0];
    OSAlarm alarm;
    u8 pad108[8];
} CardControl;

extern CardControl __CARDBlock[];
extern void OSCancelAlarm(OSAlarm *alarm);
extern BOOL EXILock(s32 chan, u32 dev, EXICallback callback);
extern BOOL EXIUnlock(s32 chan);
extern s32 __CARDReadStatus(s32 chan, void *status);
extern s32 __CARDClearStatus(s32 chan);
extern s32 Retry(s32 chan);

static inline s32 CheckStatus(const u8 *status)
{
    return (*status & 0x18) ? -5 : 0;
}

void __CARDExiHandler(s32 chan)
{
    CardControl *card = &__CARDBlock[chan];
    CardCallback callback;
    s32 result;
    u8 status;

    OSCancelAlarm(&card->alarm);
    if (!card->attached) {
        return;
    }
    if (!EXILock(chan, 0, 0)) {
        result = -128;
        goto complete;
    }
    result = __CARDReadStatus(chan, &status);
    if (result >= 0) {
        result = __CARDClearStatus(chan);
        if (result >= 0) {
            if ((result = CheckStatus(&status)) == -5 && --card->retry > 0) {
                result = Retry(chan);
                if (result >= 0) {
                    return;
                }
                goto complete;
            }
        }
    }
    EXIUnlock(chan);
complete:
    callback = card->callback;
    if (callback) {
        card->callback = 0;
        callback(chan, result);
    }
}
