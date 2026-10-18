typedef signed int s32;
typedef signed long long s64;
typedef unsigned int u32;
typedef unsigned char u8;

typedef void (*SICallback)(s32 chan, u32 error, void *context);

typedef struct SIPacket {
    s32 chan;
    void *output;
    u32 outputBytes;
    void *input;
    u32 inputBytes;
    SICallback callback;
    s64 fire;
} SIPacket;

typedef struct OSAlarm {
    u8 data[0x28];
} OSAlarm;

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    u32 outputBytes;
    void *callback;
} SIControl;

typedef struct SIWork {
    SIPacket packet[4];
    OSAlarm alarm[4];
    s64 typeTime[4];
    s64 xferTime[4];
} SIWork;

extern SIWork Packet_80640B68;
extern SIControl Si_802FCA20;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);
extern s64 __OSGetSystemTime(void);
extern void OSSetAlarm(OSAlarm *alarm, s64 tick,
                       void (*handler)(OSAlarm *, void *));
extern void fn_80209204(OSAlarm *alarm, void *context);
extern s32 __SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
                       u32 inputBytes, SICallback callback);

s32 SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
               u32 inputBytes, SICallback callback, s64 delay)
{
    u32 enabled;
    s64 fire;
    SIPacket *packet;
    SIWork *work;
    s64 now;
    OSAlarm *alarm;

    work = &Packet_80640B68;
    packet = &work->packet[chan];
    enabled = OSDisableInterrupts();
    if (packet->chan != -1 || Si_802FCA20.chan == chan) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    now = __OSGetSystemTime();
    if (delay == 0) {
        fire = now;
    } else {
        fire = delay + work->xferTime[chan];
    }
    if (now < fire) {
        delay = fire - now;
        alarm = (OSAlarm *)((u8 *)work + chan * sizeof(OSAlarm));
        OSSetAlarm((OSAlarm *)((u8 *)alarm + 0x80), delay, fn_80209204);
    } else if (__SITransfer(chan, output, outputBytes, input, inputBytes,
                           callback)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }

    packet->chan = chan;
    packet->output = output;
    packet->outputBytes = outputBytes;
    packet->input = input;
    packet->inputBytes = inputBytes;
    packet->callback = callback;
    packet->fire = fire;
    OSRestoreInterrupts(enabled);
    return 1;
}
