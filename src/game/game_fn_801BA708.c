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

void fn_801BA708(u32 stid, SND_ADPCMSTREAM_INFO* adpcmInfo)
{
    u32 j;
    u32 i;

    hwDisableIrq();
    i = GetPrivateIndex(stid);
    if (i != -1) {
        for (j = 0; j < 8; ++j) {
            streamInfo[i].coefTab[j][0] = adpcmInfo->coefTab[j][0];
            streamInfo[i].coefTab[j][1] = adpcmInfo->coefTab[j][1];
        }
        streamInfo[i].numCoef = 8;
        if (streamInfo[i].nextStreamHandle != 0xffffffff) {
            fn_801BA708(streamInfo[i].nextStreamHandle, adpcmInfo);
        }
    }
    hwEnableIrq();
}
