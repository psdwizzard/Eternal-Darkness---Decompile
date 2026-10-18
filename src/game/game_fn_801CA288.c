typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SynthInfo {
    char pad00[0x210];
    u8 voice_count;
    u8 max_music;
    u8 max_sfx;
    u8 studio_count;
} SynthInfo;

extern SynthInfo synthInfo;
extern u8 sndActive;
extern u8 synthIdleWaitActive;

extern int hwInit(u32*, u16, u16, u32);
extern void dataInitStack(void);
extern void dataInit(int, u32);
extern void seqInit(void);
extern void synthInit(u32, u32);
extern void streamInit(void);
extern void vsInit(void);
extern void s3dInit(u32);

static inline int DoInit(u32 mix_frequency, u32 aram_size, u32 voice_count,
                         u32 flags)
{
    int result = 0;

    dataInitStack();
    dataInit(0, aram_size);
    seqInit();
    synthIdleWaitActive = 0;
    synthInit(mix_frequency, voice_count);
    streamInit();
    vsInit();
    s3dInit(flags);
    sndActive = 1;
    return result;
}

int sndInit(u8 voices, u8 music, u8 sfx, u8 studios, u32 flags,
                u32 aram_size)
{
    int result;
    u32 frequency;

    result = 0;
    sndActive = 0;
    if (voices <= 0x40) {
        synthInfo.voice_count = voices;
    } else {
        synthInfo.voice_count = 0x40;
    }
    if (studios <= 8) {
        synthInfo.studio_count = studios;
    } else {
        synthInfo.studio_count = 8;
    }
    synthInfo.max_music = music;
    synthInfo.max_sfx = sfx;
    frequency = 0x7D00;
    result = hwInit(&frequency, synthInfo.voice_count,
                         synthInfo.studio_count, flags);
    if (result == 0) {
        result = DoInit(0x7D00, aram_size, synthInfo.voice_count, flags);
    }
    return result;
}
