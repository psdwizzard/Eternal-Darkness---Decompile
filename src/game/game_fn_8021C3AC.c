typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;
typedef signed long long s64;
typedef s64 OSTime;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm* prev;
    OSAlarm* next;
    OSTime period;
    OSTime start;
};

typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 channel, void *context);

typedef struct CardControl {
    BOOL attached;
    s32 result;
    u8 reserved08[0x1C];
    s32 mountStep;
    u8 reserved28[0x9C];
    CardCallback extCallback;
    u8 reservedC8[4];
    CardCallback exiCallback;
    u8 reservedD0[0x10];
    OSAlarm alarm;
    u8 reserved108[8];
} CardControl;

extern CardControl __CARDBlock[];
extern EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
extern void OSCancelAlarm(OSAlarm* alarm);

/* EXI external-interrupt handler: the memory card in this channel was removed. */
void __CARDExtHandler(s32 channel, void *context)
{
    CardControl *card;
    CardCallback callback;

    card = &__CARDBlock[channel];
    if (card->attached) {
        card->attached = 0;
        EXISetExiCallback(channel, 0);
        OSCancelAlarm(&card->alarm);

        callback = card->exiCallback;
        if (callback) {
            card->exiCallback = 0;
            callback(channel, -3);
        }

        if (card->result != -1) {
            card->result = -3;
        }

        callback = card->extCallback;
        if (callback && card->mountStep >= 7) {
            card->extCallback = 0;
            callback(channel, -3);
        }
    }
}
