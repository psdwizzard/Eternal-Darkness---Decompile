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
extern u8 lbl_8064D3A1;
extern u8 lbl_8064D3A4[8];
extern u8 lbl_8064D3AC[8];
extern u8 lbl_8064D3B4[8];
extern u8 lbl_8064D3BC[8];
extern u32 lbl_8064D3C4;
extern u32 lbl_8064D3C8;
extern u64 lbl_8064D3E0;
extern void fn_801C044C(u32);
extern void fn_801B797C(void*, void (*)(u32));
extern void fn_801B6768(u32);
extern void fn_801B75CC(u32);
extern void fn_801B6F1C(u32);
extern u8 fn_801CC6D4(void);
extern u16 fn_801CBCE0(u8, u8, u8, u8);
extern u16 fn_801CBD9C(u8, u8, u8, u8);
extern void fn_801CD400(void);
extern void fn_801B3770(u32);
extern void fn_801B35BC(u32);
extern void fn_801B3C14(u32, int, int);

static inline void HandleVoices(void)
{
    SynthJobTab* jobTab = &synthJobTable[lbl_8064D3A1];
    fn_801B797C(&jobTab->lowPrecision, fn_801B6768);
    fn_801B797C(&jobTab->event, fn_801B75CC);
    fn_801B797C(&jobTab->zeroOffset, fn_801B6F1C);
    lbl_8064D3A1 = (lbl_8064D3A1 + 1) & 0x1f;
}

static inline void HandleFaderTermination(SynthMasterFader* fade)
{
    switch (fade->seqMode) {
    case 1:
        fn_801B3770(fade->seqId);
        break;
    case 2:
        fn_801B35BC(fade->seqId);
        break;
    case 3:
        fn_801B3C14(fade->seqId, 0, 0);
        break;
    }
}

void fn_801B7A7C(u32 deltaTime)
{
    u32 i;
    u32 s;
    SynthMasterFader* fade;
    u32 mask;

    if (synthInfo.numSamples == 0) {
        return;
    }

    fn_801C044C(deltaTime);
    HandleVoices();
    if (fn_801CC6D4() == 0) {
        if ((lbl_8064D3C8 | lbl_8064D3C4) != 0) {
            for (i = 0, fade = synthMasterFader, mask = 1; i < 32; mask <<= 1, ++i, ++fade) {
                if ((lbl_8064D3C8 & mask) != 0) {
                    fade->volume = fade->target - fade->time * (fade->target - fade->start);
                    if ((fade->time -= fade->deltaTime) <= 0.f) {
                        fade->volume = fade->target;
                        HandleFaderTermination(fade);
                        if (((lbl_8064D3C8 &= ~mask) == 0) && (lbl_8064D3C4 == 0)) {
                            break;
                        }
                    }
                }
                if ((lbl_8064D3C4 & mask) != 0) {
                    fade->pauseVol =
                        fade->pauseTarget - fade->pauseTime * (fade->pauseTarget - fade->pauseStart);
                    if ((fade->pauseTime -= fade->pauseDeltaTime) <= 0.f) {
                        fade->pauseVol = fade->pauseTarget;
                        if (((lbl_8064D3C4 &= ~mask) == 0) && (lbl_8064D3C8 == 0)) {
                            break;
                        }
                    }
                }
            }
        }
        for (s = 0; s < 8; ++s) {
            if (lbl_8064D3BC[s] != 0xff) {
                AuxInfo info;
                for (i = 0; i < 4; ++i) {
                    info.parameter.para[i] = fn_801CBCE0(s, i, lbl_8064D3BC[s], lbl_8064D3B4[s]);
                }
                synthAuxACallback[s](1, &info, synthAuxAUser[s]);
            }
            if (lbl_8064D3AC[s] != 0xff) {
                AuxInfo info;
                for (i = 0; i < 4; ++i) {
                    info.parameter.para[i] = fn_801CBD9C(s, i, lbl_8064D3AC[s], lbl_8064D3A4[s]);
                }
                synthAuxBCallback[s](1, &info, synthAuxBUser[s]);
            }
        }
    }
    fn_801CD400();
    lbl_8064D3E0 += deltaTime;
}
