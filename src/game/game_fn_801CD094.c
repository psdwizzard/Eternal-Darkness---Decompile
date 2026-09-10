typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DSPvoice {
    u8 pad00[0x20];
    u32 currentAddr;
    u8 pad24[0x54];
    u32 smpAddr;
    u8 pad7C[0x14];
    u8 smpCompType;
    u8 pad91[0x5B];
    u8 state;
    u8 padED[7];
} DSPvoice;

extern DSPvoice* lbl_8064D4AC;

#define dspVoice lbl_8064D4AC

u32 fn_801CD094(u32 slot)
{
    int mode;
    u32 pos;
    u32 lowBits;
    int samplePos;
    DSPvoice* voice;

    voice = &dspVoice[slot];
    if (voice->state != 2) {
        return 0;
    }
    mode = voice->smpCompType;
    switch (mode) {
    case 0:
    case 1:
    case 4:
    case 5:
        pos = dspVoice[slot].currentAddr;
        samplePos = ((pos - 2 * (u32)dspVoice[slot].smpAddr) >> 4) * 0xe;
        lowBits = pos & 0xf;
        if (lowBits < 2) {
            return samplePos;
        }
        samplePos = lowBits + samplePos;
        return samplePos - 2;
    case 3:
        return (int)voice->currentAddr - (u32)voice->smpAddr;
    case 2:
        return (int)voice->currentAddr - ((u32)voice->smpAddr >> 1);
    default:
        return slot;
    }
}
