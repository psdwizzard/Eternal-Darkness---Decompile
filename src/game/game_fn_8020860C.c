typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef struct OSContext OSContext;
typedef void (*SICallback)(s32 chan, u32 error, OSContext *context);
typedef void (*SIPollingHandler)(s32 interrupt, OSContext *context);

typedef struct SIPacket {
    s32 chan;
    void *output;
    u32 outputBytes;
    void *input;
    u32 inputBytes;
    SICallback callback;
    s64 fire;
} SIPacket;

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void *input;
    SICallback callback;
    u32 type[4];
} SIControl;

typedef struct SIWork {
    SIPacket packet[4];
    u32 alarm[40];
    u64 typeTime[4];
    u64 xferTime[4];
    u32 type[16];
    SIPollingHandler pollingHandler[4];
    u32 pad[12];
    volatile u32 responseTime[4];
} SIWork;

extern SIWork Packet_80640B68;
extern SIControl Si_802FCA20;
extern u32 lbl_8064D8D0;
extern volatile u32 __SIRegs[64] : 0xCC006400;
extern u32 __OSBusClock : 0x800000F8;

extern u32 CompleteTransfer(void);
extern s64 __OSGetSystemTime(void);
extern s32 __SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
                      u32 inputBytes, SICallback callback);
extern void OSCancelAlarm(void *alarm);
extern s32 SIGetResponseRaw(s32 chan);
extern u32 VIGetCurrentLine(void);
extern s32 SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
                      u32 inputBytes, SICallback callback, u64 time);
extern void GetTypeCallback_802093FC(s32 chan, u32 error, OSContext *context);

void SIInterruptHandler_8020860C(s32 interrupt, OSContext *context)
{
    SIWork *work = &Packet_80640B68;
    SIControl *si = &Si_802FCA20;
    u32 status = __SIRegs[13];
    s32 chan;
    u32 error;
    SICallback callback;
    s32 i;
    s32 next;
    SIPacket *packet;
    u32 vcount;
    u32 poll;
    u32 *pollAddress;
    u32 interval;
    s32 busy;
    u32 *type;
    volatile u32 *response;
    SIPollingHandler *handlers;

    if ((status & 0xC0000000) == 0xC0000000) {
        chan = si->chan;
        error = CompleteTransfer();
        callback = si->callback;
        si->callback = 0;

        next = chan;
        for (i = 0; i < 4; i++) {
            ++next;
            next %= 4;
            packet = &work->packet[next];
            if (packet->chan != -1 && __OSGetSystemTime() >= packet->fire) {
                if (__SITransfer(packet->chan, packet->output,
                                packet->outputBytes, packet->input,
                                packet->inputBytes, packet->callback)) {
                    OSCancelAlarm(&work->alarm[next * 10]);
                    packet->chan = -1;
                }
                break;
            }
        }

        if (callback != 0) {
            callback(chan, error, context);
        }

        __SIRegs[14] &= (s32)0x0F000000 >> (chan * 8);
        if (*(type = &si->type[chan]) == 0x80) {
            busy = 1;
            if (work->packet[chan].chan == -1 && si->chan != chan) {
                busy = 0;
            }
            if (!busy) {
                SITransfer(chan, &lbl_8064D8D0, 1, type, 3,
                           GetTypeCallback_802093FC,
                           (((__OSBusClock / 4) / 125000) * 65) / 8);
            }
        }
    }

    if ((status & 0x18000000) == 0x18000000) {
        vcount = VIGetCurrentLine() + 1;
        response = work->responseTime;
        pollAddress = &si->poll;
        interval = (*pollAddress >> 16) & 0x3FF;

        for (i = 0; i < 4; i++) {
            if (SIGetResponseRaw(i)) {
                response[i] = vcount;
            }
        }

        /* Response collection can change the enabled polling channels. */
        poll = *pollAddress;
        for (i = 0; i < 4; i++) {
            if (poll & (0x80000000 >> (24 + i))) {
                if (response[i] == 0 ||
                    response[i] + interval / 2 < vcount) {
                    return;
                }
            }
        }

        response[0] = 0;
        work->responseTime[1] = 0;
        work->responseTime[2] = 0;
        work->responseTime[3] = 0;
        handlers = work->pollingHandler;
        for (i = 0; i < 4; i++) {
            if (handlers[i] != 0) {
                handlers[i](interrupt, context);
            }
        }
    }
}
