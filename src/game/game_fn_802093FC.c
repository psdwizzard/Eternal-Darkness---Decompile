typedef signed int s32;
typedef signed short s16;
typedef signed long long s64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef s64 OSTime;

typedef struct OSContext OSContext;
typedef void (*SICallback)(s32 chan, u32 error, OSContext* context);
typedef void (*SITypeCallback)(s32 chan, u32 type);
typedef void (*__OSInterruptHandler)(s16 interrupt, OSContext* context);

typedef struct SIPacket {
    s32 chan;
    void* output;
    u32 outputBytes;
    void* input;
    u32 inputBytes;
    SICallback callback;
    OSTime fire;
} SIPacket;

typedef struct OSAlarm {
    u8 data[0x28];
} OSAlarm;

extern u32 Type_802FCA34[4];
extern u32 __PADFixBits;

extern OSTime __OSGetSystemTime(void);
extern u16 OSGetWirelessID(s32 chan);
extern void OSSetWirelessID(s32 chan, u16 id);
extern s32 SITransfer(s32 chan, void* output, u32 outputBytes, void* input,
                      u32 inputBytes, SICallback callback, OSTime delay);

static SIPacket Packet[4];
static OSAlarm Alarm[4];
static OSTime TypeTime[4];
static OSTime XferTime[4];
static SITypeCallback TypeCallback[4][4];
static __OSInterruptHandler RDSTHandler[4];
static s32 InputBufferValid[4];
static u32 InputBuffer[4][2];
static u32 InputBufferVcount[4];
static u32 cmdFixDevice[4];

static inline void CallTypeAndStatusCallback(s32 chan, u32 type)
{
    SITypeCallback callback;
    int i;

    for (i = 0; i < 4; ++i) {
        callback = TypeCallback[chan][i];
        if (callback) {
            TypeCallback[chan][i] = 0;
            callback(chan, type);
        }
    }
}

void GetTypeCallback_802093FC(s32 chan, u32 error, OSContext* context)
{
    u32 type;
    u32 chanBit;
    s32 fix;
    u32 id;

    Type_802FCA34[chan] &= ~0x80;
    Type_802FCA34[chan] |= error;
    TypeTime[chan] = __OSGetSystemTime();

    type = Type_802FCA34[chan];

    chanBit = 0x80000000 >> chan;
    fix = (s32)(__PADFixBits & chanBit);
    __PADFixBits &= ~chanBit;

    if ((error & 0xF) || (type & 0x18000000) != 0x08000000 || !(type & 0x80000000) ||
        (type & 0x04000000)) {
        OSSetWirelessID(chan, 0);
        CallTypeAndStatusCallback(chan, Type_802FCA34[chan]);
        return;
    }

    id = (u32)(OSGetWirelessID(chan) << 8);

    if (fix && (id & 0x100000)) {
        cmdFixDevice[chan] = 0x4Eu << 24 | (id & 0xCFFF00) | 0x100000;
        Type_802FCA34[chan] = 0x80;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type_802FCA34[chan], 3, GetTypeCallback_802093FC, 0);
        return;
    }

    if (type & 0x100000) {
        if ((id & 0xCFFF00) != (type & 0xCFFF00)) {
            if (!(id & 0x100000)) {
                id = type & 0xCFFF00;
                id |= 0x100000;
                OSSetWirelessID(chan, (u16)((id >> 8) & 0xFFFF));
            }
            cmdFixDevice[chan] = 0x4E << 24 | id;
            Type_802FCA34[chan] = 0x80;
            SITransfer(chan, &cmdFixDevice[chan], 3, &Type_802FCA34[chan], 3, GetTypeCallback_802093FC, 0);
            return;
        }
    } else if (type & 0x40000000) {
        id = type & 0xCFFF00;
        id |= 0x100000;
        OSSetWirelessID(chan, (u16)((id >> 8) & 0xFFFF));
        cmdFixDevice[chan] = 0x4E << 24 | id;
        Type_802FCA34[chan] = 0x80;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type_802FCA34[chan], 3, GetTypeCallback_802093FC, 0);
        return;
    } else {
        OSSetWirelessID(chan, 0);
    }

    CallTypeAndStatusCallback(chan, Type_802FCA34[chan]);
}
