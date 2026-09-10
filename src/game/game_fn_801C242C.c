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
    u8 pad11D[0x404 - 0x11D];
} McmdVoiceState;
#pragma pack()

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceNum;
} SynthInfo;

extern SynthInfo lbl_80619C20;
extern McmdVoiceState* lbl_8064D3D0;
extern void fn_801C106C(McmdVoiceState*);
extern void fn_801C1BCC(McmdVoiceState*);
extern void fn_801B9C98(u32);
extern void fn_801CC8C4(u32);

#define synthInfo lbl_80619C20
#define synthVoice lbl_8064D3D0
#define vidRemoveVoiceReferences fn_801C106C
#define voiceFree fn_801C1BCC
#define streamKill fn_801B9C98
#define hwBreak fn_801CC8C4

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

void fn_801C242C(u16* ref)
{
    u32 i;
    u16 id;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
        if (synthVoice[i].addr == 0 && synthVoice[i].block == 0) {
            voiceKill(i);
        }
    }

    while (*ref != 0xFFFF) {
        if ((*ref & 0x8000)) {
            id = *ref & 0x3fff;
            while (id <= ref[1]) {
                for (i = 0; i < synthInfo.voiceNum; ++i) {
                    McmdVoiceState* sv = &synthVoice[i];
                    if (sv->addr != 0 && id == sv->macroId) {
                        voiceKill(i);
                    }
                }
                ++id;
            }
            ref += 2;
        } else {
            for (i = 0; i < synthInfo.voiceNum; ++i) {
                if (synthVoice[i].addr != 0 && *ref == synthVoice[i].macroId) {
                    voiceKill(i);
                }
            }
            ++ref;
        }
    }
}
