typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef u32 (*SND_STREAM_UPDATE_CALLBACK)(void* buffer1, u32 len1, void* buffer2,
                                          u32 len2, u32 user);

typedef struct SND_ADPCMSTREAM_INFO {
    s16 coefTab[8][2];
} SND_ADPCMSTREAM_INFO;

typedef struct SNDADPCMinfo {
    unsigned short numCoef;
    u8 initialPS;
    u8 loopPS;
    s16 loopY0;
    s16 loopY1;
    s16 coefTab[8][2];
} SNDADPCMinfo;

typedef struct STREAM_INFO {
    u32 stid;
    u32 flags;
    u8 state;
    u8 type;
    u8 pad0A[2];
    SND_STREAM_UPDATE_CALLBACK updateFunction;
    s16* buffer;
    u32 size;
    u32 bytes;
    u32 last;
    SNDADPCMinfo adpcmInfo;
    u32 voice;
    u32 user;
    u32 frq;
    u8 prio;
    u8 vol;
    u8 pan;
    u8 span;
    u8 auxa;
    u8 auxb;
    u8 orgPan;
    u8 orgSPan;
    u8 studio;
    u8 hwStreamHandle;
    u8 pad5E[2];
    u32 nextStreamHandle;
} STREAM_INFO;

static STREAM_INFO streamInfo[64];
extern u32 lbl_8064D3CC;
extern u32 lbl_8064D3EC;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern u32 fn_801BA6C4(u32, u32);
extern u8 fn_801CD1C0(u32);
extern u32 fn_801BB1A0(u32);

static inline u32 GeneratePublicID(void)
{
    u32 id;
    u32 i;

    do {
        id = lbl_8064D3EC++;
        if (id == (u32)-1) {
            id = lbl_8064D3EC++;
        }
        for (i = 0; i < 64; i++) {
            if (streamInfo[i].state != 0 && streamInfo[i].stid == id) {
                break;
            }
        }
    } while (i != 64);

    return id;
}

static inline void CheckOutputMode(u8* pan, u8* span)
{
    if (lbl_8064D3CC & 1) {
        *pan = 0x40;
        *span = 0;
    } else if (!(lbl_8064D3CC & 2)) {
        *span = 0;
    }
}

static inline void SetupVolumeAndPan(STREAM_INFO* si, u8 vol, u8 pan, u8 span, u8 auxa,
                                     u8 auxb)
{
    si->orgPan = pan;
    si->orgSPan = span;
    CheckOutputMode(&pan, &span);
    si->vol = vol;
    si->pan = pan;
    si->span = span;
    si->auxa = auxa;
    si->auxb = auxb;
}

u32 fn_801BA2A4(u8 prio, void* buffer, u32 samples, u32 frq, u8 vol, u8 pan,
                u8 span, u8 auxa, u8 auxb, u8 studio, u32 flags,
                SND_STREAM_UPDATE_CALLBACK updateFunction, u32 user,
                SND_ADPCMSTREAM_INFO* adpcmInfo)
{
    u32 stid;
    u32 i;
    u32 bytes;
    u32 j;

    fn_801CE2B8();

    for (i = 0; i < 64; i++) {
        if (streamInfo[i].state == 0) {
            break;
        }
    }

    if (i != 64) {
        stid = GeneratePublicID();
        streamInfo[i].stid = stid;
        streamInfo[i].flags = flags;
        bytes = fn_801BA6C4(samples, flags);
        streamInfo[i].buffer = (s16*)buffer;
        streamInfo[i].size = samples;
        streamInfo[i].bytes = bytes;
        streamInfo[i].updateFunction = updateFunction;
        streamInfo[i].voice = (u32)-1;
        if (flags & 1) {
            if (adpcmInfo != 0) {
                for (j = 0; j < 8; j++) {
                    streamInfo[i].adpcmInfo.coefTab[j][0] = adpcmInfo->coefTab[j][0];
                    streamInfo[i].adpcmInfo.coefTab[j][1] = adpcmInfo->coefTab[j][1];
                }
                streamInfo[i].adpcmInfo.numCoef = 8;
            }
            streamInfo[i].type = 1;
        } else {
            streamInfo[i].type = 0;
        }

        streamInfo[i].frq = frq;
        streamInfo[i].studio = studio;
        streamInfo[i].prio = prio;
        SetupVolumeAndPan(&streamInfo[i], vol, pan, span, auxa, auxb);
        streamInfo[i].user = user;
        streamInfo[i].nextStreamHandle = (u32)-1;
        streamInfo[i].state = 3;
        if ((streamInfo[i].hwStreamHandle = fn_801CD1C0(bytes)) != 0xFF) {
            if (!(flags & 0x10000) && !fn_801BB1A0(stid)) {
                stid = (u32)-1;
            }
        } else {
            stid = (u32)-1;
        }
        if (stid == (u32)-1) {
            streamInfo[i].state = 0;
        }
    } else {
        stid = (u32)-1;
    }

    fn_801CE280();
    return stid;
}
