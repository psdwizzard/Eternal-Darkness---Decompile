typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct McmdInputSource {
    u8 midiCtrl;
    u8 combine;
    u8 pad02[2];
    s32 scale;
} McmdInputSource;

typedef struct McmdInputSlot {
    McmdInputSource source[4];
    u16 oldValue;
    u8 numSource;
    u8 pad23;
} McmdInputSlot;

typedef struct SYNTH_LFO {
    u32 time;
    u32 period;
    s16 value;
    u16 lastValue;
} SYNTH_LFO;

typedef struct SYNTH_VOICE {
    u8 pad_000[0x90];
    u64 macStartTime;
    u8 pad_098[0x10];
    u8 timeUsedByInput;
    u8 pad_0A9[0x86];
    u8 orgNote;
    u8 pad_130[0x28];
    u32 orgVolume;
    u8 pad_15C[0x60];
    SYNTH_LFO lfo[2];
    u8 lfoUsedByInput[2];
} SYNTH_VOICE;

extern u64 lbl_8064D3E0;
extern s16 fn_801BEA3C(SYNTH_VOICE*, u32, u8);
extern u16 fn_801CAFAC(int, int, int);

#define synthRealTime lbl_8064D3E0
#define varGet fn_801BEA3C
#define inpGetMidiCtrl fn_801CAFAC

u16 fn_801CB4F8(SYNTH_VOICE* statePtr, McmdInputSlot* slotPtr, int midi, int midiSet)
{
    u32 sign;
    u32 i;
    u32 value;
    u32 ctrl;
    s32 tmp;
    s32 vtmp;

    for (value = 0, i = 0; i < slotPtr->numSource; ++i) {
        if (slotPtr->source[i].combine & 0x10) {
            tmp = (statePtr != 0 ? varGet(statePtr, 0, slotPtr->source[i].midiCtrl) : 0);
            goto combine_signed;
        }
        ctrl = slotPtr->source[i].midiCtrl;
        if (ctrl == 0x80 || ctrl == 1 || ctrl == 0xA || (u8)(ctrl - 0xA0) <= 1 || ctrl == 0x83) {
            switch ((u8)ctrl) {
            case 0xA0:
            case 0xA1:
                if (statePtr != 0) {
                    tmp = statePtr->lfo[(u8)ctrl - 0xA0].value << 1;
                    statePtr->lfoUsedByInput[(u8)ctrl - 0xA0] = 1;
                } else {
                    tmp = 0;
                }
                break;
            default:
                tmp = (inpGetMidiCtrl(ctrl, midi, midiSet) & 0xffff) - 0x2000;
                break;
            }
        combine_signed:
            tmp = (tmp * (slotPtr->source[i].scale >> 1)) >> 15;
            if (tmp < -0x2000) {
                tmp = -0x2000;
            } else if (tmp > 0x1FFF) {
                tmp = 0x1FFF;
            }
            switch (slotPtr->source[i].combine & 0xF) {
            case 0:
                value = tmp + 0x2000;
                sign = 1;
                break;
            case 1:
                if (sign != 0) {
                    vtmp = (value + tmp);
                    vtmp -= 0x2000;
                    if (vtmp < -0x2000) {
                        vtmp = -0x2000;
                    } else if (vtmp > 0x1FFF) {
                        vtmp = 0x1FFF;
                    }
                    value = vtmp + 0x2000;
                } else {
                    vtmp = value + tmp;
                    value = (vtmp > 0x3FFF) ? 0x3FFF : (vtmp < 0) ? 0 : vtmp;
                }
                break;
            case 2:
                if (sign != 0) {
                    vtmp = (s32)((value - 0x2000) * tmp) >> 13;
                } else {
                    vtmp = (tmp * value) >> 13;
                    sign = 1;
                }
                if (vtmp < -0x2000) {
                    vtmp = -0x2000;
                } else if (vtmp > 0x1FFF) {
                    vtmp = 0x1FFF;
                }
                value = vtmp + 0x2000;
                break;
            case 3:
                if (sign != 0) {
                    vtmp = (value - 0x2000) - tmp;
                    if (vtmp < -0x2000) {
                        vtmp = -0x2000;
                    } else if (vtmp > 0x1FFF) {
                        vtmp = 0x1FFF;
                    }
                    value = vtmp + 0x2000;
                } else {
                    vtmp = value - tmp;
                    value = (vtmp > 0x3FFF) ? 0x3FFF : (vtmp < 0) ? 0 : vtmp;
                }
                break;
            }
        } else {
            ctrl = slotPtr->source[i].midiCtrl;
            switch (ctrl) {
            case 0xA2:
                if (statePtr != 0) {
                    tmp = statePtr->orgNote << 7;
                } else {
                    tmp = 0;
                }
                break;
            case 0xA3:
                tmp = statePtr != 0 ? statePtr->orgVolume >> 9 : 0;
                break;
            case 0xA4:
                if (statePtr != 0) {
                    tmp = (synthRealTime - statePtr->macStartTime) >> 8;
                    if (tmp > 0x3fff) {
                        tmp = 0x3fff;
                    }
                    statePtr->timeUsedByInput = 1;
                } else {
                    tmp = 0;
                }
                break;
            default:
                tmp = inpGetMidiCtrl(ctrl, midi, midiSet) & 0xffff;
                break;
            }
            tmp = (tmp * (slotPtr->source[i].scale >> 1)) >> 15;
            if (tmp > 0x3FFF) {
                tmp = 0x3FFF;
            }
            switch (slotPtr->source[i].combine & 0xF) {
            case 0:
                value = tmp;
                sign = 0;
                break;
            case 1:
                if (sign != 0) {
                    vtmp = (value + tmp);
                    vtmp -= 0x2000;
                    if (vtmp < -0x2000) {
                        vtmp = -0x2000;
                    } else if (vtmp > 0x1FFF) {
                        vtmp = 0x1FFF;
                    }
                    value = vtmp + 0x2000;
                } else {
                    value += tmp;
                    value = (value > 0x3FFF) ? 0x3FFF : value;
                }
                break;
            case 2:
                if (sign != 0) {
                    vtmp = (s32)(tmp * (value - 0x2000)) >> 14;
                    if (vtmp < -0x2000) {
                        vtmp = -0x2000;
                    } else if (vtmp > 0x1FFF) {
                        vtmp = 0x1FFF;
                    }
                    value = vtmp + 0x2000;
                } else {
                    value = ((value * tmp) >> 0xE);
                    value = (value > 0x3FFF) ? 0x3FFF : value;
                }
                break;
            case 3:
                if (sign != 0) {
                    vtmp = (value - 0x2000) - tmp;
                    if (vtmp < -0x2000) {
                        vtmp = -0x2000;
                    } else if (vtmp > 0x1FFF) {
                        vtmp = 0x1FFF;
                    }
                    value = vtmp + 0x2000;
                } else {
                    vtmp = value - tmp;
                    value = (vtmp > 0x3FFF) ? 0x3FFF : (vtmp < 0) ? 0 : vtmp;
                }
                break;
            }
        }
    }

    *(u16*)&slotPtr->oldValue = value;
    return value;
}
