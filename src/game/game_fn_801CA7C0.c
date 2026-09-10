typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InpMidiState {
    u8 pad0000[0xC0];
    u8 ctrlByKey[8][16][0x86];
    u8 ctrl[16][0x86];
    u8 pad4C20[0x1920];
    u32 dirty[8][16];
    u8 pbRange[8][16];
} InpMidiState;

typedef struct SYNTH_VOICE {
    u8 pad_000[0x121];
    u8 midi;
    u8 midiSet;
    u8 pad_123[0xB3];
    u8 pbLowerKeyRange;
    u8 pbUpperKeyRange;
    u8 pad_1D8[0x3C];
    u32 midiDirtyFlags;
    u8 pad_218[0x1EC];
} SYNTH_VOICE;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

extern u8 lbl_8062A230[];
extern SynthInfo lbl_80619C20;
extern SYNTH_VOICE* lbl_8064D3D0;
extern void fn_801B7954(SYNTH_VOICE*);

#define gInpMidiCtrlByKey (((InpMidiState*)lbl_8062A230)->ctrlByKey)
#define gInpMidiCtrl (((InpMidiState*)lbl_8062A230)->ctrl)
#define gInpMidiDirty (((InpMidiState*)lbl_8062A230)->dirty)
#define SYNTH_CONFIGURATION (&lbl_80619C20)
#define synthVoice lbl_8064D3D0
#define synthKeyStateUpdate fn_801B7954

static inline void inpSetRPNHi(InpMidiState* st, u8 set, u8 channel, u8 value)
{
    u16 rpn;
    u32 i;
    u8 range;

    rpn = st->ctrlByKey[set][channel][100] | (st->ctrlByKey[set][channel][101] << 8);
    switch (rpn) {
    case 0:
        range = value > 24 ? 24 : value;
        st->pbRange[set][channel] = range;
        for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i) {
            if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
                synthVoice[i].pbUpperKeyRange = range;
                synthVoice[i].pbLowerKeyRange = range;
            }
        }
        break;
    default:
        break;
    }
}

static inline void inpSetRPNLo(u8 set, u8 channel, u8 value)
{
}

static inline void inpSetRPNDec(InpMidiState* st, u8 set, u8 channel)
{
    u16 rpn;
    u32 i;
    u8 range;

    rpn = st->ctrlByKey[set][channel][100] | (st->ctrlByKey[set][channel][101] << 8);
    switch (rpn) {
    case 0:
        range = st->pbRange[set][channel];
        if (range != 0) {
            --range;
        }
        st->pbRange[set][channel] = range;
        for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i) {
            if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
                synthVoice[i].pbUpperKeyRange = range;
                synthVoice[i].pbLowerKeyRange = range;
            }
        }
        break;
    default:
        break;
    }
}

static inline void inpSetRPNInc(InpMidiState* st, u8 set, u8 channel)
{
    u16 rpn;
    u32 i;
    u8 range;

    rpn = st->ctrlByKey[set][channel][100] | (st->ctrlByKey[set][channel][101] << 8);
    switch (rpn) {
    case 0:
        range = st->pbRange[set][channel];
        if (range < 24) {
            ++range;
        }
        st->pbRange[set][channel] = range;
        for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i) {
            if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
                synthVoice[i].pbUpperKeyRange = range;
                synthVoice[i].pbLowerKeyRange = range;
            }
        }
        break;
    default:
        break;
    }
}

void fn_801CA7C0(u8 ctrl, u8 channel, u8 set, u8 value)
{
    InpMidiState* st = (InpMidiState*)lbl_8062A230;
    u32 i;

    if (channel == 0xFF) {
        return;
    }

    if (set != 0xFF) {
        switch (ctrl) {
        case 6:
            inpSetRPNHi(st, set, channel, value);
            break;
        case 0x26:
            inpSetRPNLo(set, channel, value);
            break;
        case 0x60:
            inpSetRPNDec(st, set, channel);
            break;
        case 0x61:
            inpSetRPNInc(st, set, channel);
            break;
        }

        st->ctrlByKey[set][channel][ctrl] = value & 0x7f;
        for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i) {
            if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
                synthVoice[i].midiDirtyFlags = 0x1FFF;
                synthKeyStateUpdate(&synthVoice[i]);
            }
        }
        st->dirty[set][channel] = 0xFF;
    } else {
        switch (ctrl) {
        case 6:
            inpSetRPNHi(st, set, channel, value);
            break;
        case 0x26:
            inpSetRPNLo(set, channel, value);
            break;
        case 0x60:
            inpSetRPNDec(st, set, channel);
            break;
        case 0x61:
            inpSetRPNInc(st, set, channel);
            break;
        }

        st->ctrl[channel][ctrl] = value & 0x7f;
        for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; ++i) {
            if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
                synthVoice[i].midiDirtyFlags = 0x1FFF;
                synthKeyStateUpdate(&synthVoice[i]);
            }
        }
    }
}
