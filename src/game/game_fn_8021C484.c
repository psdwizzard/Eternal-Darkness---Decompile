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

extern CardControl lbl_80641C60[];
extern void fn_8020A93C(OSAlarm *alarm);
extern BOOL EXILock(s32 chan, u32 dev, EXICallback callback);
extern BOOL EXIUnlock(s32 chan);
extern s32 fn_8021C788(s32 chan, void *status);
extern s32 fn_8021C878(s32 chan);
extern s32 fn_8021C9C8(s32 chan);

static inline s32 CheckStatus(const u8 *status)
{
    return (*status & 0x18) ? -5 : 0;
}

void fn_8021C484(s32 chan)
{
    CardControl *card = &lbl_80641C60[chan];
    CardCallback callback;
    s32 result;
    u8 status;

    fn_8020A93C(&card->alarm);
    if (!card->attached) {
        return;
    }
    if (!EXILock(chan, 0, 0)) {
        result = -128;
        goto complete;
    }
    result = fn_8021C788(chan, &status);
    if (result >= 0) {
        result = fn_8021C878(chan);
        if (result >= 0) {
            if ((result = CheckStatus(&status)) == -5 && --card->retry > 0) {
                result = fn_8021C9C8(chan);
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
