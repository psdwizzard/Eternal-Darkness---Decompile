typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SND_ADPCMSTREAM_INFO {
    s16 coefTab[8][2];
} SND_ADPCMSTREAM_INFO;

typedef struct STREAM_INFO {
    u32 stid;
    u32 flags;
    u8 state;
    u8 type;
    u8 pad0A[2];
    u32 (*updateFunction)(void*, u32, void*, u32, u32);
    s16* buffer;
    u32 size;
    u32 bytes;
    u32 last;
    u16 numCoef;
    u8 pad22[6];
    s16 coefTab[8][2];
    u32 voice;
    u32 user;
    u32 frq;
    u8 prio;
    u8 vol;
    u8 pan;
    u8 span;
    u8 auxa;
    u8 auxb;
    u8 origPan;
    u8 origSPan;
    u8 studio;
    u8 hwStreamHandle;
    u8 pad5E[2];
    u32 nextStreamHandle;
} STREAM_INFO;

static STREAM_INFO streamInfo[64];

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

#define hwDisableIrq fn_801CE2B8
#define hwEnableIrq fn_801CE280

extern u32 fn_801C1FE0(u8);
#define voiceBlock fn_801C1FE0


static inline u32 GetPrivateIndex(u32 publicID)
{
    u32 i;
    for (i = 0; i < 64; ++i) {
        if (streamInfo[i].state != 0 && publicID == streamInfo[i].stid) {
            return i;
        }
    }
    return -1;
}

u32 fn_801BB1A0(u32 stid)
{
    u32 i;
    u32 ret = 0;

    hwDisableIrq();
    i = GetPrivateIndex(stid);
    if (i != -1) {
        if (streamInfo[i].state == 3) {
            if ((streamInfo[i].voice = voiceBlock(streamInfo[i].prio)) == -1) {
                hwEnableIrq();
                return 0;
            }
            streamInfo[i].last = 0;
            streamInfo[i].state = 1;
        }
        if (streamInfo[i].nextStreamHandle != 0xffffffff) {
            ret = fn_801BB1A0(streamInfo[i].nextStreamHandle);
        } else {
            ret = 1;
        }
    }
    hwEnableIrq();
    return ret;
}
