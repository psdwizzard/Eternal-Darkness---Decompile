typedef unsigned char u8;
typedef signed int s32;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

typedef struct StreamInfo {
    u8 pad00[8];
    u8 state;
    u8 pad09[0x5B];
} StreamInfo;

extern u8 streamCallCnt;
extern u8 streamCallDelay;
extern s32 nextPublicID;
extern SynthInfo synthInfo;
extern StreamInfo lbl_8061AE48[];

void streamInit(void)
{
    s32 i;

    streamCallCnt = 0;
    streamCallDelay = 3;
    for (i = 0; i < synthInfo.voiceCount; ++i) {
        lbl_8061AE48[i].state = 0;
    }
    nextPublicID = 0;
}
