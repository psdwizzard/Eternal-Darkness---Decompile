typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*SICallback)(s32 chan, u32 error, void *context);

typedef struct SIPacket {
    s32 chan;
    void *output;
    u32 outputBytes;
    void *input;
    u32 inputBytes;
    SICallback callback;
    unsigned long long fire;
} SIPacket;

typedef struct OSAlarm {
    u8 data[0x28];
} OSAlarm;

extern SIPacket Packet_80640B68[4];
extern OSAlarm Alarm[4];

extern s32 __SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
                       u32 inputBytes, SICallback callback);

void fn_80209204(OSAlarm *alarm, void *context)
{
    volatile u8 stack[8];
    SIPacket *packet = &Packet_80640B68[alarm - Alarm];

    if (packet->chan != -1 &&
        __SITransfer(packet->chan, packet->output, packet->outputBytes,
                    packet->input, packet->inputBytes, packet->callback)) {
        packet->chan = -1;
    }
}
