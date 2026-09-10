typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef unsigned long long u64;

typedef struct McmdVoiceState {
    u8 pad_000[0xF4];
    u32 id;
    u8 pad_0F8[0x1C];
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 pad_11C[0x13];
    u8 orgNote;
    u8 pad_130[0x28];
    u32 orgVolume;
} McmdVoiceState;

typedef struct McmdCommandArgs {
    u32 flags;
    u32 value;
} McmdCommandArgs;

typedef struct AdsrLinear {
    u16 atime;
    u16 dtime;
    u16 slevel;
    u16 rtime;
} AdsrLinear;

typedef struct AdsrDls {
    u32 atime;
    u32 dtime;
    u16 slevel;
    u16 rtime;
    s32 ascale;
    s32 dscale;
} AdsrDls;

typedef union McmdAdsrData {
    AdsrLinear linear;
    AdsrDls dls;
} McmdAdsrData;

typedef struct ADSR_INFO {
    McmdAdsrData data;
} ADSR_INFO;

extern void* fn_801BD08C(u16);
extern void fn_801CC914(u8, McmdAdsrData*, int);
extern f32 lbl_80252F2C[];

#define dataGetCurve fn_801BD08C
#define hwSetADSR fn_801CC914
#define voiceAdsrSustainTable lbl_80252F2C
#define MAC_CFLAGS(v) (*(u64*)&(v)->cFlagsHi)

void fn_801BDE7C(McmdVoiceState* svoice, McmdCommandArgs* cstep)
{
    s32 ascale;
    s32 dscale;
    McmdAdsrData adsr;
    ADSR_INFO* adsr_ptr;

    if ((adsr_ptr = (ADSR_INFO*)dataGetCurve(cstep->flags >> 8)) != 0) {
        if (!(u8)(cstep->flags >> 24)) {
            adsr.linear.atime = adsr_ptr->data.linear.atime >> 8 | adsr_ptr->data.linear.atime << 8;
            adsr.linear.dtime = adsr_ptr->data.linear.dtime >> 8 | adsr_ptr->data.linear.dtime << 8;
            adsr.linear.slevel = adsr_ptr->data.linear.slevel >> 8 | adsr_ptr->data.linear.slevel << 8;
            adsr.linear.rtime = adsr_ptr->data.linear.rtime >> 8 | adsr_ptr->data.linear.rtime << 8;
            hwSetADSR(svoice->id & 0xFF, &adsr, 0);
        } else {
            f32 sScale = voiceAdsrSustainTable[(u16)(adsr_ptr->data.dls.slevel >> 8 | adsr_ptr->data.dls.slevel << 8) >> 5];
            adsr.dls.atime = ((u8*)&adsr_ptr->data.dls.atime)[0] << 0 | ((u8*)&adsr_ptr->data.dls.atime)[1] << 8 |
                             ((u8*)&adsr_ptr->data.dls.atime)[2] << 16 | ((u8*)&adsr_ptr->data.dls.atime)[3] << 24;
            adsr.dls.dtime = ((u8*)&adsr_ptr->data.dls.dtime)[0] << 0 | ((u8*)&adsr_ptr->data.dls.dtime)[1] << 8 |
                             ((u8*)&adsr_ptr->data.dls.dtime)[2] << 16 | ((u8*)&adsr_ptr->data.dls.dtime)[3] << 24;
            adsr.dls.slevel = 4096.0f * sScale;
            adsr.dls.rtime = adsr_ptr->data.dls.rtime >> 8 | adsr_ptr->data.dls.rtime << 8;
            ascale = ((u8*)&adsr_ptr->data.dls.ascale)[0] << 0 | ((u8*)&adsr_ptr->data.dls.ascale)[1] << 8 |
                     ((u8*)&adsr_ptr->data.dls.ascale)[2] << 16 | ((u8*)&adsr_ptr->data.dls.ascale)[3] << 24;
            dscale = ((u8*)&adsr_ptr->data.dls.dscale)[0] << 0 | ((u8*)&adsr_ptr->data.dls.dscale)[1] << 8 |
                     ((u8*)&adsr_ptr->data.dls.dscale)[2] << 16 | ((u8*)&adsr_ptr->data.dls.dscale)[3] << 24;

            if (ascale != 0x80000000) {
                adsr.dls.atime += (s32)(1.1920928955078125e-7f * svoice->orgVolume * ascale);
            }

            if (dscale != 0x80000000) {
                adsr.dls.dtime += (s32)(0.0078125f * svoice->orgNote * dscale);
            }

            hwSetADSR(svoice->id & 0xFF, &adsr, 1);
        }

        MAC_CFLAGS(svoice) |= 0x100;
    }
}
