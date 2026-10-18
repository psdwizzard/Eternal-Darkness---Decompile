typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Block32 { u32 word[8]; } Block32;
typedef struct Entry {
    u8 pad00[0x18]; u32 mesgCallBackUserValue; u32 prio; u32 pad20; u32 changed[19];
    u16 smp_id; u16 pad72; Block32 smp_info; u8 pad94[0x10]; u8 adsrMode;
    u8 padA5[0x13]; u32 aTime; u32 dTime; u16 sLevel;
    u8 padC2[2]; u32 rTime; u8 padC8[0x1C]; u8 lastPitch; u8 lastVol; u8 lastVolA; u8 lastVolB;
    u8 padE8[8]; u32 flags;
} Entry;

extern Entry* dspVoice;
extern u8 salTimeOffset;
extern void hwSetSRCType(u32, u32);
extern void hwSetPolyPhaseFilter(u32, u32);
extern void hwSetITDMode(u32, u32);

void hwInitSamplePlayback(u32 voiceIndex, u16 sampleId, Block32* sampleInfo, u32 resetAdsr, u32 priority,
                 u32 callbackUserValue, u32 resetSrc, u32 itdMode)
{
    u8 timeOffset;
    u32 breakFlags;

    breakFlags = 0;
    for (timeOffset = 0; timeOffset <= salTimeOffset; timeOffset++) {
        breakFlags |= dspVoice[voiceIndex].changed[timeOffset] & 0x20;
        dspVoice[voiceIndex].changed[timeOffset] = 0;
    }

    dspVoice[voiceIndex].changed[0] = breakFlags;
    dspVoice[voiceIndex].prio = priority;
    dspVoice[voiceIndex].mesgCallBackUserValue = callbackUserValue;
    dspVoice[voiceIndex].flags = 0;
    dspVoice[voiceIndex].smp_id = sampleId;
    dspVoice[voiceIndex].smp_info = *sampleInfo;

    if (resetAdsr != 0) {
        dspVoice[voiceIndex].adsrMode = 0;
        dspVoice[voiceIndex].aTime = 0;
        dspVoice[voiceIndex].dTime = 0;
        dspVoice[voiceIndex].sLevel = 0x7fff;
        dspVoice[voiceIndex].rTime = 0;
    }

    dspVoice[voiceIndex].lastPitch = 0xff;
    dspVoice[voiceIndex].lastVol = 0xff;
    dspVoice[voiceIndex].lastVolA = 0xff;
    dspVoice[voiceIndex].lastVolB = 0xff;

    if (resetSrc != 0) {
        hwSetSRCType(voiceIndex, 0);
        hwSetPolyPhaseFilter(voiceIndex, 1);
    }
    hwSetITDMode(voiceIndex, itdMode);
}
