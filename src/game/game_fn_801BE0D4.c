typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;

typedef struct ADSR_INFO {
    union {
        struct {
            s32 atime;
            s32 dtime;
            u16 slevel;
            u16 rtime;
            s32 ascale;
            s32 dscale;
        } dls;
        struct {
            u16 atime;
            u16 dtime;
            u16 slevel;
            u16 rtime;
        } linear;
    } data;
} ADSR_INFO;

typedef struct McmdAdsrData {
    union {
        struct {
            s32 atime;
            s32 dtime;
            u16 slevel;
            u16 rtime;
        } dls;
    };
} McmdAdsrData;

typedef struct ADSR_VARS {
    u8 mode;
    u8 state;
    u32 cnt;
    u32 currentVolume;
    u32 currentIndex;
    u32 currentDelta;
    u32 aTime;
    u32 dTime;
    u16 sLevel;
    u32 rTime;
    u16 cutOff;
    u8 aMode;
} ADSR_VARS;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0x114];
    u64 cflags;
    u8 pad_11C[0x13];
    u8 orgNote;
    u8 pad_130[0x28];
    u32 orgVolume;
    u8 pad_15C[0x80];
    ADSR_VARS pitchADSR;
    s16 pitchADSRRange;
} SYNTH_VOICE;
#pragma pack()

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

extern ADSR_INFO* fn_801BD08C(u16);
extern u32 fn_801C2AAC(u32);
extern void fn_801C2D74(ADSR_VARS*);
extern u8 lbl_80252B2C[];

#define voiceAdsrDecayTable lbl_80252B2C

void fn_801BE0D4(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    McmdAdsrData adsr;
    ADSR_INFO* adsr_ptr;
    u32 sl;
    s32 ascale;
    s32 dscale;

    if ((adsr_ptr = fn_801BD08C(cstep->para1 >> 8)) == 0) {
        return;
    }

    svoice->pitchADSRRange = (s8)cstep->para2 << 8;

    if (svoice->pitchADSRRange >= 0) {
        svoice->pitchADSRRange += ((s16)(s8)(cstep->para2 >> 8) << 8) / 100;
    } else {
        svoice->pitchADSRRange -= ((s16)(s8)(cstep->para2 >> 8) << 8) / 100;
    }

    adsr.dls.atime = ((u8*)&adsr_ptr->data.dls.atime)[0] << 0 | ((u8*)&adsr_ptr->data.dls.atime)[1] << 8 |
                     ((u8*)&adsr_ptr->data.dls.atime)[2] << 16 | ((u8*)&adsr_ptr->data.dls.atime)[3] << 24;
    adsr.dls.dtime = ((u8*)&adsr_ptr->data.dls.dtime)[0] << 0 | ((u8*)&adsr_ptr->data.dls.dtime)[1] << 8 |
                     ((u8*)&adsr_ptr->data.dls.dtime)[2] << 16 | ((u8*)&adsr_ptr->data.dls.dtime)[3] << 24;
    adsr.dls.slevel = adsr_ptr->data.dls.slevel >> 8 | adsr_ptr->data.dls.slevel << 8;
    adsr.dls.rtime = adsr_ptr->data.dls.rtime >> 8 | adsr_ptr->data.dls.rtime << 8;
    ascale = ((u8*)&adsr_ptr->data.dls.ascale)[0] << 0 | ((u8*)&adsr_ptr->data.dls.ascale)[1] << 8 |
             ((u8*)&adsr_ptr->data.dls.ascale)[2] << 16 | ((u8*)&adsr_ptr->data.dls.ascale)[3] << 24;
    dscale = ((u8*)&adsr_ptr->data.dls.dscale)[0] << 0 | ((u8*)&adsr_ptr->data.dls.dscale)[1] << 8 |
             ((u8*)&adsr_ptr->data.dls.dscale)[2] << 16 | ((u8*)&adsr_ptr->data.dls.dscale)[3] << 24;

    if (ascale != 0x80000000) {
        f32 prod = 1.1920928955078125e-7f * svoice->orgVolume;
        adsr.dls.atime += (s32)(prod * ascale);
    }
    if (dscale != 0x80000000) {
        f32 prod = 0.0078125f * svoice->orgNote;
        adsr.dls.dtime += (s32)(prod * dscale);
    }

    svoice->pitchADSR.mode = 1;
    svoice->pitchADSR.aMode = 0;
    svoice->pitchADSR.aTime = fn_801C2AAC(adsr.dls.atime);
    svoice->pitchADSR.dTime = fn_801C2AAC(adsr.dls.dtime);
    if ((sl = adsr.dls.slevel >> 2) > 0x3ff) {
        sl = 0x3ff;
    }
    svoice->pitchADSR.sLevel = 0xc1 - voiceAdsrDecayTable[sl];
    svoice->pitchADSR.rTime = adsr.dls.rtime;
    fn_801C2D74(&svoice->pitchADSR);
    svoice->cflags |= 0x20000000000ULL;
}
