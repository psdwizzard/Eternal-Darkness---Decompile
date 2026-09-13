typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct SynthMasterFader {
    float volume;
    float target;
    float start;
    float time;
    float deltaTime;
    float pauseVol;
    u8 pad18[0x15];
    u8 type;
    u8 pad2E[2];
} SynthMasterFader;

typedef struct SynthJob {
    u32 word00;
    u32 word04;
    u32 word08;
    u32 word0C;
    u32 word10;
    u32 word14;
    u32 word18;
    u32 word1C;
    u32 word20;
    u32 word24;
    u32 word28;
    u32 word2C;
    u32 word30;
    u32 word34;
    u32 word38;
    u32 word3C;
    u32 word40;
    u32 word44;
    u32 word48;
    u32 word4C;
    u32 word50;
    u32 word54;
    u32 word58;
    u32 word5C;
} SynthJob;

typedef struct SynthITDDefault {
    u8 music;
    u8 sfx;
} SynthITDDefault;

typedef struct SynthState {
    u8 pad000[0x200];
    u32 bpmTicks;
    u8 pad204[0x3C];
    SynthJob jobs[4];
    u32 sampleRate;
    u8 pad3C4[0x210];
    SynthMasterFader masterFader[32];
    u8 padBD4[0x60];
    void (*auxACallback[8])(void);
    u8 padC54[0x20];
    void (*auxBCallback[8])(void);
    SynthITDDefault itdDefault[8];
    u32 globalVariable[16];
} SynthState;

extern SynthState lbl_80619860;
extern u64 lbl_8064D3E0;
extern u32 lbl_8064D3CC;
extern void* lbl_8064D3D4;
extern u8* lbl_8064D3D0;
extern u32 lbl_8064D3C8;
extern u32 lbl_8064D3C4;
extern u8 lbl_8064D3BC[8];
extern u8 lbl_8064D3AC[8];
extern u8 lbl_8064D3A1;

extern void* memset(void*, int, u32);
extern void* fn_801CE330(u32);
extern void fn_801CBE58(void*);
extern void fn_801C0ED8(void);
extern void fn_801C0F40(void);
extern void fn_801C1CB0(void);
extern void fn_801C27D0(void);
extern void fn_801CC6FC(void*);
extern int fn_801B85F0(int, u32);

#define SYNTH_VOICE_STRIDE 0x404
#define synthVoice lbl_8064D3D0

void fn_801B86C0(u32 sampleRate, u32 voiceCount)
{
    u32 voiceIndex;
    u32 fadeIndex;
    u32 auxIndex;
    float unusedA[2];
    SynthState* synth = &lbl_80619860;

    lbl_8064D3E0 = 0;
    synth->sampleRate = sampleRate;
    synth->bpmTicks = 0x1800;
    lbl_8064D3CC = 0;
    lbl_8064D3D4 = 0;

    synthVoice = fn_801CE330(voiceCount * SYNTH_VOICE_STRIDE);
    memset(synthVoice, 0, voiceCount * SYNTH_VOICE_STRIDE);

    for (voiceIndex = 0; voiceIndex < voiceCount; voiceIndex++) {
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0xF4) = 0xFFFFFFFF;
        *(u64*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x114) = 0;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x110) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x10C) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x121) = 0xFF;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x154) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x192) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x190) = 0x80;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x191) = 0;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x180) = 0x400000;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x170) = 0x400000;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x184) = 0;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x174) = 0;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1A0) = 0;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1A4) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1B8) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1B9) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x11C) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x11E) = 0x17;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x104) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x193) = 1;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1C0) = 0;
        *(u16*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1C4) = 0;
        *(u16*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1C6) = 0x7FFF;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1CC) = 0;
        *(u16*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1D0) = 0;
        *(u16*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x1D2) = 0x7FFF;
        *(u32*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x13C) = 0x6400;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x131) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x11F) = 0;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x08) = (u8)voiceIndex;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x09) = 0xFF;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x14) = (u8)voiceIndex;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x15) = 0xFF;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x20) = (u8)voiceIndex;
        *(u8*)((u8*)synthVoice + voiceIndex * SYNTH_VOICE_STRIDE + 0x21) = 0xFF;
    }

    {
        SynthMasterFader* fade = synth->masterFader;
        u32 pass;

        for (pass = 0; pass < 2; pass++) {
            fade[0].volume = 0.f;
            fade[0].pauseVol = 1.f;
            fade[0].type = 4;
            fade[1].volume = 0.f;
            fade[1].pauseVol = 1.f;
            fade[1].type = 4;
            fade[2].volume = 0.f;
            fade[2].pauseVol = 1.f;
            fade[2].type = 4;
            fade[3].volume = 0.f;
            fade[3].pauseVol = 1.f;
            fade[3].type = 4;
            fade[4].volume = 0.f;
            fade[4].pauseVol = 1.f;
            fade[4].type = 4;
            fade[5].volume = 0.f;
            fade[5].pauseVol = 1.f;
            fade[5].type = 4;
            fade[6].volume = 0.f;
            fade[6].pauseVol = 1.f;
            fade[6].type = 4;
            fade[7].volume = 0.f;
            fade[7].pauseVol = 1.f;
            fade[7].type = 4;
            fade[8].volume = 0.f;
            fade[8].pauseVol = 1.f;
            fade[8].type = 4;
            fade[9].volume = 0.f;
            fade[9].pauseVol = 1.f;
            fade[9].type = 4;
            fade[10].volume = 0.f;
            fade[10].pauseVol = 1.f;
            fade[10].type = 4;
            fade[11].volume = 0.f;
            fade[11].pauseVol = 1.f;
            fade[11].type = 4;
            fade[12].volume = 0.f;
            fade[12].pauseVol = 1.f;
            fade[12].type = 4;
            fade[13].volume = 0.f;
            fade[13].pauseVol = 1.f;
            fade[13].type = 4;
            fade[14].volume = 0.f;
            fade[14].pauseVol = 1.f;
            fade[14].type = 4;
            fade[15].volume = 0.f;
            fade[15].pauseVol = 1.f;
            fade[15].type = 4;
            fade += 16;
        }
    }

    lbl_8064D3C8 = 0;
    lbl_8064D3C4 = 0;
    synth->masterFader[31].type = 1;
    for (fadeIndex = 0; fadeIndex < 8; fadeIndex++) {
        synth->masterFader[fadeIndex + 23].type = 0;
    }
    synth->masterFader[21].volume = 1.f;
    synth->masterFader[22].volume = 1.f;

    fn_801CBE58(0);

    for (auxIndex = 0; auxIndex < 8; auxIndex++) {
        synth->auxACallback[auxIndex] = 0;
        lbl_8064D3BC[auxIndex] = 0xFF;
        synth->auxBCallback[auxIndex] = 0;
        lbl_8064D3AC[auxIndex] = 0xFF;
        synth->itdDefault[auxIndex].sfx = 0;
        synth->itdDefault[auxIndex].music = 0;
    }

    fn_801C0ED8();
    fn_801C0F40();
    fn_801C1CB0();

    for (auxIndex = 0; auxIndex < 16; auxIndex++) {
        synth->globalVariable[auxIndex] = 0;
    }

    fn_801C27D0();

    {
        SynthJob* job = synth->jobs;
        for (auxIndex = 0; (u8)auxIndex < 0x20; auxIndex += 8) {
            job->word00 = 0;
            job->word04 = 0;
            job->word08 = 0;
            job->word0C = 0;
            job->word10 = 0;
            job->word14 = 0;
            job->word18 = 0;
            job->word1C = 0;
            job->word20 = 0;
            job->word24 = 0;
            job->word28 = 0;
            job->word2C = 0;
            job->word30 = 0;
            job->word34 = 0;
            job->word38 = 0;
            job->word3C = 0;
            job->word40 = 0;
            job->word44 = 0;
            job->word48 = 0;
            job->word4C = 0;
            job->word50 = 0;
            job->word54 = 0;
            job->word58 = 0;
            job->word5C = 0;
            job++;
        }
    }
    lbl_8064D3A1 = 0;
    fn_801CC6FC(fn_801B85F0);
}
