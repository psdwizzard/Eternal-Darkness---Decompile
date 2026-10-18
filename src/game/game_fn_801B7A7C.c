typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef union AuxInfo {
    struct {
        long* left;
        long* right;
        long* surround;
    } buffer;
    struct {
        u16 para[4];
    } parameter;
} AuxInfo;

typedef void (*AuxCallback)(u8 reason, AuxInfo* info, void* user);

typedef struct SynthJobTab {
    void* lowPrecision;
    void* event;
    void* zeroOffset;
} SynthJobTab;

typedef struct SynthMasterFader {
    float volume;
    float target;
    float start;
    float time;
    float deltaTime;
    float pauseVol;
    float pauseTarget;
    float pauseStart;
    float pauseTime;
    float pauseDeltaTime;
    u32 seqId;
    u8 seqMode;
    u8 pad2D[3];
} SynthMasterFader;

typedef struct SynthInfo {
    u32 mixFrq;
    u32 numSamples;
    u8 pad08[0x20C];
} SynthInfo;

static u32 synthTicksPerSecond[9][16];
static SynthJobTab synthJobTable[32];
static SynthInfo synthInfo;
static SynthMasterFader synthMasterFader[32];
static u8 synthTrackVolume[64];
static void* synthAuxAUser[8];
static AuxCallback synthAuxACallback[8];
static void* synthAuxBUser[8];
static AuxCallback synthAuxBCallback[8];
extern u8 synthJobTableIndex;
extern u8 synthAuxBMIDISet[8];
extern u8 synthAuxBMIDI[8];
extern u8 synthAuxAMIDISet[8];
extern u8 synthAuxAMIDI[8];
extern u32 synthMasterFaderPauseActiveFlags;
extern u32 synthMasterFaderActiveFlags;
extern u64 synthRealTime;
extern void macHandle(u32);
extern void HandleJobQueue(void*, void (*)(u32));
extern void LowPrecisionHandler(u32);
extern void EventHandler(u32);
extern void ZeroOffsetHandler(u32);
extern u8 hwGetTimeOffset(void);
extern u16 inpGetAuxA(u8, u8, u8, u8);
extern u16 inpGetAuxB(u8, u8, u8, u8);
extern void hwFrameDone(void);
extern void seqStop(u32);
extern void seqPause(u32);
extern void seqMute(u32, int, int);

static inline void HandleVoices(void)
{
    SynthJobTab* jobTab = &synthJobTable[synthJobTableIndex];
    HandleJobQueue(&jobTab->lowPrecision, LowPrecisionHandler);
    HandleJobQueue(&jobTab->event, EventHandler);
    HandleJobQueue(&jobTab->zeroOffset, ZeroOffsetHandler);
    synthJobTableIndex = (synthJobTableIndex + 1) & 0x1f;
}

static inline void HandleFaderTermination(SynthMasterFader* fade)
{
    switch (fade->seqMode) {
    case 1:
        seqStop(fade->seqId);
        break;
    case 2:
        seqPause(fade->seqId);
        break;
    case 3:
        seqMute(fade->seqId, 0, 0);
        break;
    }
}

void synthHandle(u32 deltaTime)
{
    u32 i;
    u32 s;
    SynthMasterFader* fade;
    u32 mask;

    if (synthInfo.numSamples == 0) {
        return;
    }

    macHandle(deltaTime);
    HandleVoices();
    if (hwGetTimeOffset() == 0) {
        if ((synthMasterFaderActiveFlags | synthMasterFaderPauseActiveFlags) != 0) {
            for (i = 0, fade = synthMasterFader, mask = 1; i < 32; mask <<= 1, ++i, ++fade) {
                if ((synthMasterFaderActiveFlags & mask) != 0) {
                    fade->volume = fade->target - fade->time * (fade->target - fade->start);
                    if ((fade->time -= fade->deltaTime) <= 0.f) {
                        fade->volume = fade->target;
                        HandleFaderTermination(fade);
                        if (((synthMasterFaderActiveFlags &= ~mask) == 0) && (synthMasterFaderPauseActiveFlags == 0)) {
                            break;
                        }
                    }
                }
                if ((synthMasterFaderPauseActiveFlags & mask) != 0) {
                    fade->pauseVol =
                        fade->pauseTarget - fade->pauseTime * (fade->pauseTarget - fade->pauseStart);
                    if ((fade->pauseTime -= fade->pauseDeltaTime) <= 0.f) {
                        fade->pauseVol = fade->pauseTarget;
                        if (((synthMasterFaderPauseActiveFlags &= ~mask) == 0) && (synthMasterFaderActiveFlags == 0)) {
                            break;
                        }
                    }
                }
            }
        }
        for (s = 0; s < 8; ++s) {
            if (synthAuxAMIDI[s] != 0xff) {
                AuxInfo info;
                for (i = 0; i < 4; ++i) {
                    info.parameter.para[i] = inpGetAuxA(s, i, synthAuxAMIDI[s], synthAuxAMIDISet[s]);
                }
                synthAuxACallback[s](1, &info, synthAuxAUser[s]);
            }
            if (synthAuxBMIDI[s] != 0xff) {
                AuxInfo info;
                for (i = 0; i < 4; ++i) {
                    info.parameter.para[i] = inpGetAuxB(s, i, synthAuxBMIDI[s], synthAuxBMIDISet[s]);
                }
                synthAuxBCallback[s](1, &info, synthAuxBUser[s]);
            }
        }
    }
    hwFrameDone();
    synthRealTime += deltaTime;
}
