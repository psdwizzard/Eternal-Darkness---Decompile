typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0x34];
    void* addr;
    u8 pad_038[0xCC];
    u8 keyGroup;
    u8 pad_105[0x0F];
    u64 cflags;
    u8 pad_11C[0x2E8];
} SYNTH_VOICE;
#pragma pack()

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

extern SynthInfo lbl_80619C20;
extern SYNTH_VOICE* lbl_8064D3D0;
extern void fn_801C0644(SYNTH_VOICE*);
extern void fn_801C2148(u32);

#define synthVoice lbl_8064D3D0

void fn_801BEE6C(SYNTH_VOICE* state, MSTEP* args)
{
    u32 i;
    u8 kg;
    u32 kill;
    SYNTH_VOICE* voice;

    state->keyGroup = 0;
    kg = (u8)(args->para1 >> 8);
    kill = (u8)(args->para1 >> 0x10) != 0;
    if (kg != 0) {
        for (i = 0; i < lbl_80619C20.voiceCount; i++) {
            voice = &synthVoice[i];
            if (voice->addr != 0 && (voice->cflags & 2) == 0 && kg == voice->keyGroup) {
                if (kill == 0) {
                    fn_801C0644(voice);
                } else {
                    fn_801C2148(i);
                }
            }
        }
        state->keyGroup = kg;
    }
}
