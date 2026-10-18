typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct McmdVoiceState {
    u8 pad000[0x34];
    u32 addr;
    u8 pad038[0x102 - 0x38];
    u16 macroId;
    u8 pad104[0x110 - 0x104];
    u32 age;
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 block;
    u8 fxFlag;
    u8 pad11E[0x404 - 0x11E];
} McmdVoiceState;
#pragma pack()

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceNum;
} SynthInfo;

extern SynthInfo synthInfo;
extern McmdVoiceState* synthVoice;
extern void vidRemoveVoiceReferences(McmdVoiceState*);
extern void voiceFree(McmdVoiceState*);
extern void streamKill(u32);
extern void hwBreak(u32);


static inline void voiceKill(u32 voice)
{
    McmdVoiceState* voiceState = &synthVoice[voice];

    if (voiceState->addr != 0) {
        vidRemoveVoiceReferences(voiceState);
        *(u64*)&voiceState->cFlagsHi &= ~3;
        voiceState->age = 0;
        voiceFree(voiceState);
    }
    if (voiceState->block != 0) {
        streamKill(voice);
    }
    hwBreak(voice);
}

void synthKillAllVoices(u8 musicOnly)
{
    u32 i;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
        McmdVoiceState* sv = &synthVoice[i];
        if (sv->addr != 0) {
            if (musicOnly == 0 || (musicOnly != 0 && sv->fxFlag == 0)) {
                voiceKill(i);
            }
        } else {
            voiceKill(i);
        }
    }
}
