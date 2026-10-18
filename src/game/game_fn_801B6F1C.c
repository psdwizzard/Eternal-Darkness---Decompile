typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;

typedef struct SynthFader {
    f32 volume;
    u8 pad04[0x10];
    f32 pauseVol;
    u8 pad18[0x30 - 0x18];
} SynthFader;

typedef struct SynthState {
    u8 pad000[0x5D4];
    SynthFader masterFader[23];
    u8 padA24[0xBD4 - 0xA24];
    u8 trackVolume[0x40];
} SynthState;

typedef struct McmdVoiceState {
    u8 pad000[0x2C];
    u32 lastZeroCallTimeHi;
    u32 lastZeroCallTimeLo;
    u32 addr;
    u8 pad038[0xA8 - 0x38];
    u8 timeUsedByInput;
    u8 pad0A9[0x10C - 0xA9];
    u8 prio;
    u8 pad10D;
    u16 ageSpeed;
    u32 age;
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 pad11C;
    u8 fxFlag;
    u8 vGroup;
    u8 pad11F;
    u8 track;
    u8 pad121[0x154 - 0x121];
    u32 volume;
    u8 pad158[4];
    f32 lastVolFaderScale;
    u32 lastPan;
    u32 lastSPan;
    f32 treCurScale;
    u16 treScale;
    u16 treModAddScale;
    u32 panning[2];
    u8 pad178[0x190 - 0x178];
    u8 revVolScale;
    u8 revVolOffset;
    u8 volTable;
    u8 pad193;
    s32 envDelta;
    s32 envTarget;
    s32 envCurrent;
    u8 pad1A0[0x214 - 0x1A0];
    u32 midiDirtyFlags;
    u8 pad218[0x400 - 0x218];
    u16 curOutputVolume;
    u8 pad402[2];
} McmdVoiceState;

extern SynthState synthTicksPerSecond;
extern McmdVoiceState* synthVoice;
extern u32 synthFlags;
extern u64 synthRealTime;
extern u32 hwIsActive(u32);
extern u16 inpGetModulation(McmdVoiceState*);
extern u16 inpGetTremolo(McmdVoiceState*);
extern u16 inpGetPanning(McmdVoiceState*);
extern u16 inpGetSurPanning(McmdVoiceState*);
extern u16 inpGetVolume(McmdVoiceState*);
extern u16 inpGetReverb(McmdVoiceState*);
extern u16 inpGetPreAuxA(McmdVoiceState*);
extern u16 inpGetPostAuxB(McmdVoiceState*);
extern u16 inpGetPreAuxB(McmdVoiceState*);
extern u8 hwGetTimeOffset(void);
extern void hwSetVolume(u32, u8, u32, u32, f32, f32, f32);
extern void hwSetPriority(u32, u32);
extern void synthAddJob(void*, int, u32);

#define synthMasterFader synth->masterFader
#define synthTrackVolume synth->trackVolume
#define HWVOICE(i) (&synthVoice[i])
#define HWVOICE_FLAGS(sv) (*(u64*)&(sv)->cFlagsHi)

static inline void UpdateTimeMIDICtrl(McmdVoiceState* sv)
{
    if (sv->timeUsedByInput != 0) {
        sv->timeUsedByInput = 0;
        sv->midiDirtyFlags = 0x1FFF;
    }
}

void ZeroOffsetHandler(int voice)
{
    McmdVoiceState* sv;
    u32 lowDeltaTime;
    u16 Modulation;
    f32 vol;
    f32 auxa;
    f32 auxb;
    f32 faderVol;
    f32 voiceVol;
    u32 volUpdate;
    f32 lfo;
    f32 scale;
    s32 pan;
    s32 fxIndex;
    f32 postVol;
    SynthState* synth = &synthTicksPerSecond;

    sv = HWVOICE(voice);
    if (hwIsActive(voice) || sv->addr != 0) {
        lowDeltaTime = (u32)(synthRealTime - *(u64*)&sv->lastZeroCallTimeHi);
        *(u64*)&sv->lastZeroCallTimeHi = synthRealTime;

        if ((HWVOICE_FLAGS(sv) & 0x8000) != 0) {
            sv->envCurrent += sv->envDelta * (lowDeltaTime >> 8);
            if (sv->envDelta < 0) {
                if (sv->envTarget >= sv->envCurrent) {
                    sv->envCurrent = sv->envTarget;
                    HWVOICE_FLAGS(sv) &= ~0x8000;
                }
            } else if (sv->envTarget <= sv->envCurrent) {
                sv->envCurrent = sv->envTarget;
                HWVOICE_FLAGS(sv) &= ~0x8000;
            }
            sv->volume = sv->envCurrent;
            volUpdate = 1;
        } else {
            volUpdate = (HWVOICE_FLAGS(sv) & 0x100000000000ULL) != 0;
        }

        HWVOICE_FLAGS(sv) &= ~0x100000000000ULL;

        fxIndex = sv->fxFlag ? 22 : 21;
        vol = synthMasterFader[sv->vGroup].pauseVol * synthMasterFader[sv->vGroup].volume;
        faderVol = vol * synthMasterFader[fxIndex].volume;

        if (sv->track != 0xFF) {
            vol = (1.f / 127.f) * (faderVol * (f32)synthTrackVolume[sv->track]);
        } else {
            vol = faderVol;
        }

        if (vol != sv->lastVolFaderScale) {
            sv->lastVolFaderScale = vol;
            volUpdate = 1;
        }

        voiceVol = (1.f / (8192.f * 1016.f)) * (f32)sv->volume;

        if ((sv->treScale | sv->treModAddScale) != 0) {
            Modulation = inpGetModulation(sv);
            lfo = (1.f / 8192.f) * (f32)(0x2000 - ((0x2000 - ((s16)inpGetTremolo(sv) - 0x2000)) >> 1));
            {
                f32 modScale = 1.490207e-08f * ((f32)Modulation * (f32)(0x1000 - sv->treModAddScale));
                scale = (1.f / 4096.f) * ((f32)sv->treScale * (1.f - modScale));
            }
            if (sv->treCurScale < scale) {
                if ((sv->treCurScale += 0.2f) > scale) {
                    sv->treCurScale = scale;
                }
            } else if (sv->treCurScale > scale) {
                if ((sv->treCurScale -= 0.2f) < scale) {
                    sv->treCurScale = scale;
                }
            }
            {
                f32 tmp = lfo * (1.f - sv->treCurScale);
                voiceVol = voiceVol * (1.f - tmp);
            }
            volUpdate = 1;
        }

        if ((synthFlags & 1) == 0) {
            if ((HWVOICE_FLAGS(sv) & 0x200000000000ULL) != 0 || (sv->midiDirtyFlags & 0x6) != 0) {
                HWVOICE_FLAGS(sv) &= ~0x200000000000ULL;
                pan = sv->panning[0] + (inpGetPanning(sv) - 0x2000) * 0x200;
                sv->lastPan = pan < 0 ? 0 : (pan > 0x7F0000 ? 0x7F0000 : pan);

                if ((synthFlags & 2) != 0) {
                    if ((sv->lastSPan = sv->panning[1] + inpGetSurPanning(sv) * 0x200) > 0x7F0000) {
                        sv->lastSPan = 0x7F0000;
                    }
                } else {
                    sv->lastSPan = 0;
                }
                volUpdate = 1;
            } else if ((synthFlags & 2) == 0) {
                sv->lastSPan = 0;
            }
        } else {
            sv->lastPan = 0x400000;
            sv->lastSPan = 0;
            volUpdate |= (HWVOICE_FLAGS(sv) & 0x200000000000ULL) != 0;
            HWVOICE_FLAGS(sv) &= ~0x200000000000ULL;
        }

        if (volUpdate || (sv->midiDirtyFlags & 0xF01) != 0) {
            postVol = (1.f / 16383.f) * (voiceVol * vol * (f32)inpGetVolume(sv));
            auxa = (1.f / 127.f) * (f32)sv->revVolOffset +
                   ((1.f / 16383.f) * (voiceVol * (f32)inpGetPreAuxA(sv)) +
                    (1.f / 127.f) * ((f32)sv->revVolScale * ((1.f / 16383.f) * (postVol * (f32)inpGetReverb(sv)))));
            auxb = (1.f / 16383.f) * (voiceVol * (f32)inpGetPreAuxB(sv)) +
                   (1.f / 16383.f) * (postVol * (f32)inpGetPostAuxB(sv));
            sv->curOutputVolume = (u16)(32767.f * postVol);
            hwSetVolume(voice, sv->volTable, sv->lastPan, sv->lastSPan, postVol, auxa, auxb);
        }

        if (sv->age != 0) {
            if ((s32)(sv->age -= sv->ageSpeed * lowDeltaTime) < 0) {
                sv->age = 0;
            }
            hwSetPriority(voice, sv->prio << 24 | sv->age >> 15);
        }

        synthAddJob((void*)sv, 1, (5 - hwGetTimeOffset()) * 256);
    }
    UpdateTimeMIDICtrl(sv);
}
