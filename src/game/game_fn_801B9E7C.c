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

extern void fn_801CD138(void*, u32, u32, u8, u32, u32);
extern void fn_801CCB20(u32, u8);
#define hwFlushStream fn_801CD138
#define hwSetStreamLoopPS fn_801CCB20

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

void fn_801B9E7C(u32 stid, u32 off1, u32 len1, u32 off2, u32 len2)
{
    u32 i;

    hwDisableIrq();
    i = GetPrivateIndex(stid);
    if (i != -1) {
        switch (streamInfo[i].type) {
        case 0:
            off1 *= 2;
            len1 *= 2;
            off2 *= 2;
            len2 *= 2;
            break;
        case 1:
            off1 = (off1 / 14) * 8;
            len1 = ((len1 + 13) / 14) * 8;
            off2 = (off2 / 14) * 8;
            len2 = ((len2 + 13) / 14) * 8;
            break;
        }

        if (len1 != 0) {
            hwFlushStream(streamInfo[i].buffer, off1, len1, streamInfo[i].hwStreamHandle, 0, 0);
        }

        if (len2 != 0) {
            hwFlushStream(streamInfo[i].buffer, off2, len2, streamInfo[i].hwStreamHandle, 0, 0);
        }

        if (streamInfo[i].type == 1) {
            hwSetStreamLoopPS(streamInfo[i].voice, *(u32*)((u32)streamInfo[i].buffer + 0x40000000) >> 24);
        }
    }
    hwEnableIrq();
}
