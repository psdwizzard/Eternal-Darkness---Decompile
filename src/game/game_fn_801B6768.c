typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct SynthLfo {
    u32 time;
    u32 period;
    s16 value;
    s16 lastValue;
} SynthLfo;

typedef struct McmdVoiceState {
    u8 pad000[0x24];
    u32 lastLowCallTimeHi;
    u32 lastLowCallTimeLo;
    u8 pad02C[0x34 - 0x2C];
    u32 addr;
    u8 pad038[0xA8 - 0x38];
    u8 timeUsedByInput;
    u8 pad0A9[0x114 - 0xA9];
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 pad11C[5];
    u8 midi;
    u8 midiSet;
    u8 pad123;
    u32 sInfo;
    u8 pad128[4];
    u16 curNote;
    s8 curDetune;
    u8 orgNote;
    u8 lastNote;
    u8 portType;
    u16 portLastCtrlState;
    u32 portDuration;
    u32 portCurPitch;
    u32 portTime;
    u8 vibKeyRange;
    u8 vibCentRange;
    u8 pad142[2];
    u32 vibPeriod;
    u32 vibCurTime;
    s32 vibCurOffset;
    s16 vibModAddScale;
    u8 pad152[0x170 - 0x152];
    u32 panning[2];
    u32 panDelta[2];
    u32 panTarget[2];
    u32 panTime[2];
    u8 pad190[0x1A0 - 0x190];
    u32 sweepOff[2];
    s32 sweepAdd[2];
    s32 sweepCnt[2];
    u8 sweepNum[2];
    u8 pad1BA[2];
    SynthLfo lfo[2];
    u8 lfoUsedByInput[2];
    u8 pbLowerKeyRange;
    u8 pbUpperKeyRange;
    u16 pbLast;
    u8 pad1DA[2];
    u8 pitchADSR[0x1E4 - 0x1DC];
    s32 pitchADSRCurrentVolume;
    u8 pad1E8[0x204 - 0x1E8];
    s16 pitchADSRRange;
    u16 curPitch;
    u8 pad208[0x214 - 0x208];
    u32 midiDirtyFlags;
    u8 pad218[0x404 - 0x218];
} McmdVoiceState;

extern McmdVoiceState* lbl_8064D3D0;
extern u64 lbl_8064D3E0;
extern u32 fn_801CC6DC(u32);
extern s16 fn_801CC304(u16);
extern u32 fn_801C30D4(void*, u16*, u16*);
extern u16 fn_801CBA58(McmdVoiceState*);
extern u16 fn_801CBAE8(McmdVoiceState*);
extern u16 fn_801CAFAC(u8, u8, u8);
extern u16 fn_801C29BC(u8, u32);
extern u16 fn_801C2980(u16);
extern u16 fn_801CBAA0(McmdVoiceState*);
extern void fn_801CCB98(u32, u16);
extern void fn_801B775C(void*, int, u32);

#define synthVoice lbl_8064D3D0
#define synthRealTime lbl_8064D3E0
#define HWVOICE(i) (&synthVoice[i])
#define HWVOICE_FLAGS(sv) (*(u64*)&(sv)->cFlagsHi)
#define hwIsActive fn_801CC6DC
#define sndSin fn_801CC304
#define adsrHandleLowPrecision fn_801C30D4
#define inpGetPitchBend fn_801CBA58
#define inpGetModulation fn_801CBAE8
#define inpGetMidiCtrl fn_801CAFAC
#define voiceGetPitchRatio fn_801C29BC
#define voiceScaleSampleRate fn_801C2980
#define inpGetDoppler fn_801CBAA0
#define hwSetPitch fn_801CCB98
#define synthAddJob fn_801B775C

static inline u32 apply_portamento(McmdVoiceState* svoice, u32 ccents, u32 deltaTime)
{
    u32 old_portCurPitch;

    if ((HWVOICE_FLAGS(svoice) & 0x400) != 0 && (s32)((svoice->portDuration - svoice->portTime) >> 8) > 0) {
        old_portCurPitch = svoice->portCurPitch;
        svoice->portCurPitch += (s32)deltaTime * ((s32)(ccents - svoice->portCurPitch) >> 8) / (s32)((svoice->portDuration - svoice->portTime) >> 8);
        if ((old_portCurPitch < ccents && svoice->portCurPitch < ccents) || (old_portCurPitch > ccents && svoice->portCurPitch > ccents)) {
            ccents = svoice->portCurPitch;
            svoice->portTime += deltaTime;
        } else {
            svoice->portTime = svoice->portDuration;
        }
    }
    return ccents;
}

static inline u32 convert_cents(McmdVoiceState* svoice, u32 ccents)
{
    u32 curDetune;
    u32 cpitch;

    cpitch = voiceGetPitchRatio(ccents >> 16, svoice->sInfo) << 16;
    if ((curDetune = ccents & 0xFFFF) != 0) {
        cpitch += curDetune * ((u16)voiceScaleSampleRate(cpitch >> 16) - (cpitch >> 16));
    }
    return cpitch;
}

static inline void UpdateTimeMIDICtrl(McmdVoiceState* sv)
{
    if (sv->timeUsedByInput != 0) {
        sv->timeUsedByInput = 0;
        sv->midiDirtyFlags = 0x1FFF;
    }
}

void fn_801B6768(int voice)
{
    u32 j;
    s32 pbend;
    u32 ccents;
    u32 cpitch;
    u16 Modulation;
    u16 portamentoRaw;
    u32 lowDeltaTime;
    McmdVoiceState* sv;
    u32 cntDelta;
    u32 addFactor;
    u16 adsr_start;
    u16 adsr_delta;
    s32 vrange;
    s32 voff;
    sv = HWVOICE(voice);
    if (hwIsActive(voice) || sv->addr != 0) {
        lowDeltaTime = (u32)(synthRealTime - *(u64*)&sv->lastLowCallTimeHi);
        *(u64*)&sv->lastLowCallTimeHi = synthRealTime;

        for (j = 0; j < 2; ++j) {
            if (sv->lfo[j].period == 0) {
                continue;
            }
            sv->lfo[j].time += lowDeltaTime;
            sv->lfo[j].value = sndSin((u16)((sv->lfo[j].time % sv->lfo[j].period * 16) / (sv->lfo[j].period / 256)));
            if (sv->lfo[j].value != sv->lfo[j].lastValue) {
                sv->lfo[j].lastValue = sv->lfo[j].value;
                if (sv->lfoUsedByInput[j]) {
                    sv->lfoUsedByInput[j] = 0;
                    sv->midiDirtyFlags |= 0x1FFF;
                }
            }
        }

        if ((HWVOICE_FLAGS(sv) & 0x2000) != 0) {
            sv->vibCurTime += lowDeltaTime;
            sv->vibCurOffset = sndSin((u16)((sv->vibCurTime % sv->vibPeriod * 16) / (sv->vibPeriod / 256)));
        }

        if (sv->sweepNum[0] | sv->sweepNum[1]) {
            cntDelta = (lowDeltaTime << 8) >> 4;
            addFactor = (lowDeltaTime << 4) >> 4;
            for (j = 0; j < 2; ++j) {
                if (sv->sweepNum[j] == 0) {
                    continue;
                }
                sv->sweepCnt[j] -= cntDelta;
                if (sv->sweepCnt[j] <= 0) {
                    sv->sweepCnt[j] = sv->sweepNum[j] << 16;
                    sv->sweepOff[j] = 0;
                } else {
                    sv->sweepOff[j] += (sv->sweepAdd[j] >> 12) * addFactor;
                }
            }
        }

        for (j = 0; j < 2; ++j) {
            u32 panVal;
            if (sv->panning[j] == sv->panTarget[j]) {
                continue;
            }
            sv->panTime[j] -= lowDeltaTime;
            if ((s32)sv->panTime[j] <= 0) {
                sv->panning[j] = sv->panTarget[j];
                sv->panTime[j] = 0;
            } else {
                sv->panning[j] = sv->panTarget[j] - (sv->panTime[j] / 256) * sv->panDelta[j];
                panVal = sv->panning[j];
                sv->panning[j] = (s32)panVal < 0 ? 0 : panVal > 0x7F0000 ? 0x7F0000 : panVal;
            }
            HWVOICE_FLAGS(sv) |= 0x200000000000ULL;
        }

        if ((HWVOICE_FLAGS(sv) & 0x20000000000ULL) != 0 && adsrHandleLowPrecision(&sv->pitchADSR, &adsr_start, &adsr_delta)) {
            HWVOICE_FLAGS(sv) &= ~0x20000000000ULL;
        }

        ccents = (sv->curNote << 16) + (sv->curDetune * 0x10000) / 100;
        do {
            if ((HWVOICE_FLAGS(sv) & 0x10010) != 0) {
                if (sv->midi == 0xFF) {
                    continue;
                }
                pbend = inpGetPitchBend(sv);
                sv->pbLast = pbend;
            } else {
                pbend = sv->pbLast;
            }
            if (pbend != 0x2000) {
                if ((pbend -= 0x2000) < 0) {
                    ccents += sv->pbLowerKeyRange * pbend * 8;
                } else {
                    ccents += sv->pbUpperKeyRange * pbend * 8;
                }
            }
        } while (0);

        if ((HWVOICE_FLAGS(sv) & 0x2000) != 0) {
            Modulation = inpGetModulation(sv);
            vrange = sv->vibKeyRange * 256 + (sv->vibCentRange * 256) / 100;
            if (sv->vibModAddScale != 0) {
                vrange += (sv->vibModAddScale * ((Modulation >> 7) & 0x1FF)) >> 7;
            }
            if ((HWVOICE_FLAGS(sv) & 0x4000) != 0) {
                voff = (sv->vibCurOffset * ((Modulation >> 7) & 0x1FF)) >> 7;
            } else {
                voff = sv->vibCurOffset;
            }
            ccents += (vrange * voff) >> 4;
        }

        if (sv->midi != 0xFF) {
            portamentoRaw = inpGetMidiCtrl(0x41, sv->midi, sv->midiSet);
            if (portamentoRaw != sv->portLastCtrlState || (HWVOICE_FLAGS(sv) & 0x21000) == 0x20000) {
                if (portamentoRaw <= 0x1F80) {
                    HWVOICE_FLAGS(sv) &= ~0x400;
                } else {
                    if ((HWVOICE_FLAGS(sv) & 0x400) == 0) {
                        if ((HWVOICE_FLAGS(sv) & 0x20000) == 0) {
                            if (sv->portType == 1) {
                                if ((HWVOICE_FLAGS(sv) & 0x1000) == 0) {
                                    sv->portTime = 0;
                                } else {
                                    sv->portTime = sv->portDuration;
                                }
                            } else {
                                sv->portTime = sv->portDuration;
                            }
                            sv->portCurPitch = sv->lastNote << 16;
                        }
                    }
                    HWVOICE_FLAGS(sv) |= 0x400;
                }
                HWVOICE_FLAGS(sv) |= 0x1000;
                sv->portLastCtrlState = portamentoRaw;
            }
        }

        ccents = apply_portamento(sv, ccents, lowDeltaTime);

        if ((HWVOICE_FLAGS(sv) & 0x20000000000ULL) != 0) {
            ccents += sv->pitchADSRRange * ((s32)sv->pitchADSRCurrentVolume >> 16) >> 7;
        }

        cpitch = convert_cents(sv, ccents);
        cpitch += sv->sweepOff[0] + sv->sweepOff[1];
        hwSetPitch(voice, sv->curPitch = ((cpitch >> 16) * inpGetDoppler(sv)) >> 13);
        synthAddJob((void*)sv, 0, 0xF00);
    }
    UpdateTimeMIDICtrl(sv);
}
