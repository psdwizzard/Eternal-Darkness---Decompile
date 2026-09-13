typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef float f32;

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

typedef struct VID_LIST {
    struct VID_LIST* next;
    struct VID_LIST* prev;
    u32 vid;
    u32 root;
} VID_LIST;

typedef struct CALLSTACK {
    u8* addr;
    u8* curAddr;
} CALLSTACK;

typedef struct SYNTH_LFO {
    u32 time;
    u32 period;
    u16 value;
    u16 lastValue;
} SYNTH_LFO;

typedef struct ADSR_INFO {
    s32 atime;
    s32 dtime;
    u16 slevel;
    u16 rtime;
    s32 ascale;
    s32 dscale;
} ADSR_INFO;

typedef struct INPUT_SLOT {
    u8 bytes[0x24];
} INPUT_SLOT;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0x34];
    u8* addr;
    u8* curAddr;
    u8 pad_03C[0x14];
    u8* trapEventAddr[3];
    u8* trapEventCurAddr[3];
    u8 trapEventAny;
    u8 pad_069[3];
    CALLSTACK callStack[4];
    u8 callStackEntryNum;
    u8 callStackIndex;
    u8 pad_08E[2];
    u64 macStartTime;
    u8 pad_098[8];
    u64 waitTime;
    u8 pad_0A8[2];
    u16 loop;
    u32 local_vars[16];
    u8 pad_0EC[8];
    u32 id;
    VID_LIST* vidList;
    u8 pad_0FC[8];
    u8 keyGroup;
    u8 pad_105[3];
    u32 lastVID;
    u8 prio;
    u8 pad_10D;
    u16 ageSpeed;
    u32 age;
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 pad_11C[2];
    u8 vGroup;
    u8 studio;
    u8 track;
    u8 midi;
    u8 midiSet;
    u8 section;
    u32 sInfo;
    u32 playFrq;
    u16 curNote;
    s8 curDetune;
    u8 orgNote;
    u8 lastNote;
    u8 portType;
    u16 portLastCtrlState;
    u32 portDuration;
    u8 pad_138[4];
    u32 portTime;
    u8 pad_140[0x10];
    s16 vibModAddScale;
    u8 pad_152[2];
    u32 volume;
    u32 orgVolume;
    u8 pad_15C[0xC];
    f32 treCurScale;
    u16 treScale;
    u16 treModAddScale;
    u32 panning[2];
    u32 panDelta[2];
    u32 panTarget[2];
    u32 panTime[2];
    u8 revVolScale;
    u8 revVolOffset;
    u8 volTable;
    u8 itdMode;
    u8 pad_194[0xC];
    u32 sweepOff[2];
    u32 sweepAdd[2];
    u32 sweepCnt[2];
    u8 sweepNum[2];
    u8 pad_1BA[2];
    SYNTH_LFO lfo[2];
    u8 pad_1D4[2];
    u8 pbLowerKeyRange;
    u8 pbUpperKeyRange;
    u16 pbLast;
    u8 pad_1DA[0x2E];
    u8 setupVol;
    u8 setupPan;
    u8 setupMidi;
    u8 setupMidiSet;
    u8 setupSection;
    u8 setupTrack;
    u8 setupVGroup;
    u8 setupStudio;
    u8 setupItdMode;
    u8 pad_211[7];
    INPUT_SLOT inpVolume;
    INPUT_SLOT inpPanning;
    INPUT_SLOT inpSurroundPanning;
    INPUT_SLOT inpPitchBend;
    INPUT_SLOT inpDoppler;
    INPUT_SLOT inpModulation;
    INPUT_SLOT inpPedal;
    INPUT_SLOT inpPortamento;
    INPUT_SLOT inpPreAuxA;
    INPUT_SLOT inpReverb;
    INPUT_SLOT inpPreAuxB;
    INPUT_SLOT inpPostAuxB;
    INPUT_SLOT inpTremolo;
    u8 mesgNum;
    u8 mesgRead;
    u8 mesgWrite;
    u8 pad_3EF;
    u32 mesgQueue[4];
    u16 curOutputVolume;
    u8 pad_402[2];
} SYNTH_VOICE;
#pragma pack()

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

extern u8 lbl_80252160[];
extern u8 lbl_8064D438;
extern u64 lbl_8064D448;
extern MSTEP lbl_8064D450;
extern f32 lbl_80650F40;
extern f32 lbl_80650F44;
extern INPUT_SLOT lbl_8061A9C4[8][4];
extern INPUT_SLOT lbl_8061A544[8][4];
extern SynthInfo lbl_80619C20;
extern u32 lbl_8061A504[];
extern f32 lbl_80252F2C[];
extern u8 lbl_80252B2C[];
extern SYNTH_VOICE* lbl_8064D3D0;

extern void fn_801CC8C4(u8);
extern void fn_801CBE58(SYNTH_VOICE*);
extern u8 fn_801CB4B4(u8, u8);
extern void fn_801CB470(u8, u8, u8);
extern void fn_801C26F8(SYNTH_VOICE*);
extern u16 fn_801CAFAC(int, int, int);
extern u8* fn_801CB238(u8, u8);
extern void* memset(void*, int, u32);
extern void fn_801B78AC(SYNTH_VOICE*);
extern void fn_801C106C(SYNTH_VOICE*);
extern void fn_801C1BCC(SYNTH_VOICE*);
extern u8* fn_801BCEB0(u16);
extern u32 fn_801BD398(SYNTH_VOICE*, MSTEP*);
extern void fn_801BD6A0(SYNTH_VOICE*, MSTEP*);
extern void fn_801BD7F8(SYNTH_VOICE*, MSTEP*);
extern void fn_801C0644(SYNTH_VOICE*);
extern u16 fn_801CBAE8(SYNTH_VOICE*);
extern void fn_801BDE7C(SYNTH_VOICE*, MSTEP*);
extern u32 fn_801BE3F4(u32, u16);
extern void fn_801BE354(SYNTH_VOICE*, MSTEP*, u8);
extern void fn_801BE474(SYNTH_VOICE*, MSTEP*, u32);
extern void fn_801BD990(SYNTH_VOICE*, MSTEP*);
extern void fn_801B7954(SYNTH_VOICE*);
extern u32 fn_801CC2E4(void);
extern u32 fn_800F5C54(f32);
extern void fn_801CC914(u8, ADSR_INFO*, u32);
extern void fn_801BE5A0(SYNTH_VOICE*, MSTEP*);
extern u32 fn_801C267C(SYNTH_VOICE*);
extern void fn_801BE874(SYNTH_VOICE*, MSTEP*);
extern void fn_801BDB6C(SYNTH_VOICE*, MSTEP*);
extern u32 fn_801CD228(u32);
extern void fn_801BDCEC(SYNTH_VOICE*);
extern void fn_801BE0D4(SYNTH_VOICE*, MSTEP*);
extern void fn_801BEC38(SYNTH_VOICE*, MSTEP*);
extern void fn_801BEAA4(SYNTH_VOICE*, u32, u8, s32);
extern void fn_801CC704(u32, u32);
extern void fn_801C1600(SYNTH_VOICE*, u8);
extern void fn_801BE740(SYNTH_VOICE*, INPUT_SLOT*, MSTEP*, u64, u32);
extern void fn_801CC408(u32*);
extern void fn_801BEE6C(SYNTH_VOICE*, MSTEP*);
extern void fn_801CCC10(u8, u8);
extern void fn_801CCC3C(u8, u8);
extern void fn_801BEB08(SYNTH_VOICE*, MSTEP*, u8);
extern u32 fn_801CC1AC(SYNTH_VOICE*, u8);

#define MAC_CFLAGS(sv) (*(u64*)&(sv)->cFlagsHi)
#define MAC_FLAG64(hi, lo) (((u64)(hi) << 32) | (lo))
#define SYNTH_GLOBAL_REG(index) (lbl_8061A504[(index) - 0x10])
#define macCurrentCmd lbl_8064D450
#define macStepsThisFrame lbl_8064D438
#define macRealTime lbl_8064D448
#define synthVoice lbl_8064D3D0
#define SYNTH_CONFIGURATION (&lbl_80619C20)
#define voiceAdsrSustainTable lbl_80252F2C
#define voiceAdsrDecayTable lbl_80252B2C
#define inpAuxA lbl_8061A9C4
#define inpAuxB lbl_8061A544
#define hwBreak fn_801CC8C4
#define inpInit fn_801CBE58
#define inpGetMidiLastNote fn_801CB4B4
#define inpSetMidiLastNote fn_801CB470
#define voiceSetLastStarted fn_801C26F8
#define inpGetMidiCtrl fn_801CAFAC
#define inpGetChannelDefaults fn_801CB238
#define synthStartSynthJobHandling fn_801B78AC
#define vidRemoveVoiceReferences fn_801C106C
#define voiceFree fn_801C1BCC
#define dataGetMacro fn_801BCEB0
#define mcmdWait fn_801BD398
#define mcmdLoop fn_801BD6A0
#define mcmdPlayMacro fn_801BD7F8
#define macSetExternalKeyoff fn_801C0644
#define inpGetModulation fn_801CBAE8
#define mcmdSetADSR fn_801BDE7C
#define TranslateVolume fn_801BE3F4
#define voiceConfigureParamRamp fn_801BE354
#define mcmdScaleVolume fn_801BE474
#define mcmdStartSample fn_801BD990
#define synthKeyStateUpdate fn_801B7954
#define sndRand fn_801CC2E4
#define hwSetADSR fn_801CC914
#define mcmdRandomKey fn_801BE5A0
#define voiceIsLastStarted fn_801C267C
#define mcmdPortamento fn_801BE874
#define mcmdVibrato fn_801BDB6C
#define hwExitStream fn_801CD228
#define DoSetPitch fn_801BDCEC
#define mcmdSetPitchADSR fn_801BE0D4
#define mcmdSendMessage fn_801BEC38
#define varSet32 fn_801BEAA4
#define hwSetPriority fn_801CC704
#define voiceSetPriority fn_801C1600
#define SelectSource fn_801BE740
#define sndConvertMs fn_801CC408
#define mcmdSetKeyGroup fn_801BEE6C
#define hwSetSRCType fn_801CCC10
#define hwSetPolyPhaseFilter fn_801CCC3C
#define mcmdVarCalculation fn_801BEB08
#define inpGetExCtrl fn_801CC1AC

static inline s32 varGetReg(SYNTH_VOICE* state, u32 useExCtrl, u8 index)
{
    if (useExCtrl != 0) {
        return (u16)inpGetExCtrl(state, index);
    }
    index &= 0x1f;
    if (index < 0x10) {
        return state->local_vars[index];
    }
    return SYNTH_GLOBAL_REG(index);
}

static inline int SendSingleKeyOff(u32 voiceid)
{
    u32 i;

    if (voiceid != 0xffffffff) {
        i = voiceid & 0xff;
        if (voiceid == synthVoice[i].id) {
            macSetExternalKeyoff(&synthVoice[i]);
            return 0;
        }
    }
    return -1;
}

static inline void mcmdUntrapEvent(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    u8 i;

    svoice->trapEventAddr[(cstep->para1 >> 8) & 0xff] = 0;
    for (i = 0; i < 3; i++) {
        if (svoice->trapEventAddr[i] != 0) {
            return;
        }
    }
    svoice->trapEventAny = 0;
}

static inline void mcmdGetVID(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    if ((u8)(cstep->para1 >> 0x10) == 0) {
        varSet32(svoice, 0, (u8)(cstep->para1 >> 8), svoice->vidList->vid);
    } else {
        varSet32(svoice, 0, (u8)(cstep->para1 >> 8), svoice->lastVID);
    }
}

static inline void mcmdAddPriority(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    s16 delta;
    s16 prio;

    delta = cstep->para1 >> 0x10;
    prio = svoice->prio + delta;
    prio = prio < 0 ? 0 : prio > 0xff ? 0xff : prio;
    voiceSetPriority(svoice, prio);
}

static inline void mcmdSetAgeCounterByVolume(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    u32 age;

    age = (svoice->volume >> 0x10) & 0xff;
    age = (cstep->para2 & 0xffff) * age;
    age = (cstep->para1 >> 0x10) + ((s32)age >> 7);
    svoice->age = age > 60000 ? 0x75300000 : age << 0xf;
    hwSetPriority(svoice->id & 0xff, ((u32)svoice->prio << 0x18) | (svoice->age >> 0xf));
}

static inline void mcmdIfVarCompare(SYNTH_VOICE* svoice, MSTEP* cstep, u8 cmp)
{
    s32 lhs;
    s32 rhs;
    u8 result;

    lhs = varGetReg(svoice, (cstep->para1 >> 8) & 0xff, (cstep->para1 >> 0x10) & 0xff);
    rhs = varGetReg(svoice, cstep->para1 >> 0x18, (u8)cstep->para2);

    switch (cmp) {
    case 0:
        result = !(rhs - lhs);
        break;
    case 1:
        result = lhs < rhs;
        break;
    }

    if ((cstep->para2 >> 8) & 0xff) {
        result = !result;
    }
    if (result != 0) {
        u16 step = cstep->para2 >> 0x10;
        svoice->curAddr = (u8*)((MSTEP*)svoice->addr + step);
    }
}

static inline void mcmdIfModulation(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    u8* macro;
    u8 mod;

    if (svoice->midi == 0xff) {
        return;
    }
    mod = inpGetModulation(svoice) >> 7;
    if (mod < (u8)(cstep->para1 >> 8)) {
        return;
    }

    if ((macro = dataGetMacro(cstep->para1 >> 0x10)) != 0) {
        svoice->addr = macro;
        svoice->curAddr = macro + ((cstep->para2 & 0xffff) << 3);
    }
}

static inline void mcmdSRCModeSelect(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    hwSetSRCType(svoice->id & 0xff, (cstep->para1 >> 8) & 0xff);
    hwSetPolyPhaseFilter(svoice->id & 0xff, (u8)(cstep->para1 >> 0x10));
    MAC_CFLAGS(svoice) |= MAC_FLAG64(0x800, 0);
}

static inline void mcmdSendKeyOff(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    u32 voiceid;
    u32 i;

    voiceid = (svoice->orgNote + ((cstep->para1 >> 8) & 0xff)) << 8;
    voiceid |= ((u16)(cstep->para1 >> 0x10)) << 0x10;
    for (i = 0; i < SYNTH_CONFIGURATION->voiceCount; i++) {
        if (synthVoice[i].id == (voiceid | i)) {
            SendSingleKeyOff(voiceid | i);
        }
    }
}

void fn_801BEF40(SYNTH_VOICE* sv)
{
    u32 ex;
    u32 cmd;
    u32* cmdValuePtr;
    u8 lastNote;
    u8* channelDefaults;
    f32 one;
    f32 dlsScaleMax;
    u32 unused;
    u8* dataTables = lbl_80252160;

    if (MAC_CFLAGS(sv) & 3) {
        if (MAC_CFLAGS(sv) & 1) {
            MAC_CFLAGS(sv) &= ~MAC_FLAG64(0, 1);
            hwBreak(sv->id & 0xff);
        }

        sv->panning[0] = sv->panTarget[0] = sv->setupPan << 16;
        sv->panning[1] = sv->panTarget[1] = 0;
        sv->volume = sv->setupVol << 16;
        sv->volTable = 0;
        sv->orgVolume = sv->volume;
        sv->midi = sv->setupMidi;
        sv->midiSet = sv->setupMidiSet;
        sv->section = sv->setupSection;
        sv->track = sv->setupTrack;
        sv->itdMode = sv->setupItdMode;
        sv->keyGroup = 0;
        sv->vibModAddScale = 0;
        sv->treScale = 0;
        inpInit(sv);
        lastNote = inpGetMidiLastNote(sv->midi, sv->midiSet);
        if (lastNote != 0xff) {
            sv->lastNote = lastNote;
        } else {
            sv->lastNote = sv->orgNote;
        }

        inpSetMidiLastNote(sv->midi, sv->midiSet, sv->orgNote);
        voiceSetLastStarted(sv);
        sv->vGroup = sv->setupVGroup;
        sv->studio = sv->setupStudio;
        sv->portTime = 0;
        sv->portDuration = 25600;
        sv->portType = 0;
        if (sv->midi != 0xff) {
            sv->portLastCtrlState = inpGetMidiCtrl(0x41, sv->midi, sv->midiSet);
        } else {
            sv->portLastCtrlState = 0;
        }
        channelDefaults = inpGetChannelDefaults(sv->midi, sv->midiSet);
        sv->pbLowerKeyRange = channelDefaults[0];
        sv->pbUpperKeyRange = channelDefaults[0];
        sv->revVolScale = 128;
        sv->revVolOffset = 0;
        sv->loop = 0;
        sv->sweepNum[0] = 0;
        sv->sweepNum[1] = 0;
        sv->sweepOff[0] = 0;
        sv->sweepOff[1] = 0;
        sv->lfo[0].period = 0;
        sv->lfo[0].value = 0;
        sv->lfo[0].lastValue = 0x7fff;
        sv->lfo[1].period = 0;
        sv->lfo[1].value = 0;
        sv->lfo[1].lastValue = 0x7fff;
        sv->trapEventAddr[0] = 0;
        sv->trapEventAddr[1] = 0;
        sv->trapEventAddr[2] = 0;
        sv->trapEventAny = 0;
        sv->sInfo = 0xffffffff;
        sv->playFrq = 0xffffffff;
        sv->pbLast = 0x2000;
        sv->curOutputVolume = 0;
        MAC_CFLAGS(sv) &= MAC_FLAG64(0, 8);
        MAC_CFLAGS(sv) |= MAC_FLAG64(0x3000, 0);
        memset(sv->local_vars, 0, sizeof(sv->local_vars));
        sv->waitTime = macRealTime;
        sv->macStartTime = macRealTime;
        synthStartSynthJobHandling(sv);
    }

    macStepsThisFrame = 0;
    dlsScaleMax = lbl_80650F40;
    one = lbl_80650F44;
    cmdValuePtr = &macCurrentCmd.para2;

    do {
        if (++macStepsThisFrame > 32) {
            break;
        }

        ex = 0;
        macCurrentCmd.para1 = ((MSTEP*)sv->curAddr)->para1;
        *cmdValuePtr = ((MSTEP*)sv->curAddr)->para2;
        sv->curAddr += 8;
        cmd = macCurrentCmd.para1;

        switch (cmd & 0x7f) {
        case 0x0:
            vidRemoveVoiceReferences(sv);
            voiceFree(sv);
            ex = 1;
            break;
        case 0x1:
            vidRemoveVoiceReferences(sv);
            voiceFree(sv);
            ex = 1;
            break;
        case 0x2:
            if (sv->curNote >= (s32)((cmd >> 8) & 0xff)) {
                u8* macro = dataGetMacro(cmd >> 0x10);
                if (macro != 0) {
                    sv->addr = macro;
                    sv->curAddr = macro + ((*cmdValuePtr & 0xffff) << 3);
                }
            }
            break;
        case 0x3:
            if (((sv->volume >> 0x10) & 0xff) >= ((cmd >> 8) & 0xff)) {
                u8* macro = dataGetMacro(cmd >> 0x10);
                if (macro != 0) {
                    sv->addr = macro;
                    sv->curAddr = macro + ((*cmdValuePtr & 0xffff) << 3);
                }
            }
            break;
        case 0x4:
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        case 0x5:
            mcmdLoop(sv, &macCurrentCmd);
            break;
        case 0x6: {
            u8* macro = dataGetMacro(cmd >> 0x10);
            u32 stop;
            if (macro != 0) {
                sv->addr = macro;
                stop = 0;
                sv->curAddr = macro + ((*cmdValuePtr & 0xffff) << 3);
            } else {
                vidRemoveVoiceReferences(sv);
                voiceFree(sv);
                stop = 1;
            }
            ex = stop;
            break;
        }
        case 0x7:
            ((u8*)cmdValuePtr)[2] = 1;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        case 0x8:
            mcmdPlayMacro(sv, &macCurrentCmd);
            break;
        case 0x9:
            mcmdSendKeyOff(sv, &macCurrentCmd);
            break;
        case 0xa:
            mcmdIfModulation(sv, &macCurrentCmd);
            break;
        case 0xb: {
            s32 delta;
            s32 scale;
            delta = (sv->curNote - (s32)((cmd >> 0x10) & 0xff)) << 0x10;
            scale = (s8)(u8)(cmd >> 8);
            delta = (delta * scale) >> 7;
            delta += ((u8)(cmd >> 0x18)) << 0x10;
            delta = delta < 0 ? 0 : delta > 0x7f0000 ? 0x7f0000 : delta;
            sv->panTarget[0] = delta;
            sv->panning[0] = delta;
            break;
        }
        case 0xc:
            mcmdSetADSR(sv, &macCurrentCmd);
            break;
        case 0xd: {
            u16 scale = (u8)(cmd >> 8);
            u16 curve;
            if (((*cmdValuePtr >> 8) & 0xff) == 0) {
                sv->volume = (sv->volume * scale) / 0x7f;
            } else {
                sv->volume = (sv->orgVolume * scale) / 0x7f;
            }
            sv->volume += ((u8)(macCurrentCmd.para1 >> 0x10)) << 0x10;
            if (sv->volume > 0x7f0000) {
                sv->volume = 0x7f0000;
            }
            curve = (u8)(macCurrentCmd.para1 >> 0x18);
            curve |= ((u16)((u8)*cmdValuePtr) << 8);
            sv->volume = TranslateVolume(sv->volume, curve);
            MAC_CFLAGS(sv) |= MAC_FLAG64(0x1000, 0);
            break;
        }
        case 0xe:
            voiceConfigureParamRamp(sv, &macCurrentCmd, 0);
            break;
        case 0xf:
            mcmdScaleVolume(sv, &macCurrentCmd, sv->volume);
            break;
        case 0x10:
            mcmdStartSample(sv, &macCurrentCmd);
            break;
        case 0x11:
            hwBreak(sv->id & 0xff);
            break;
        case 0x12:
            MAC_CFLAGS(sv) |= MAC_FLAG64(0, 0x80);
            synthKeyStateUpdate(sv);
            break;
        case 0x13:
            if ((u8)sndRand() >= ((macCurrentCmd.para1 >> 8) & 0xff)) {
                u8* macro = dataGetMacro(macCurrentCmd.para1 >> 0x10);
                if (macro != 0) {
                    sv->addr = macro;
                    sv->curAddr = macro + ((*cmdValuePtr & 0xffff) << 3);
                }
            }
            break;
        case 0x14:
            mcmdScaleVolume(sv, &macCurrentCmd, 0);
            break;
        case 0x15:
            voiceConfigureParamRamp(sv, &macCurrentCmd, 1);
            break;
        case 0x16: {
            f32 sScale;
            ADSR_INFO adsr;
            s32* row;
            sScale = voiceAdsrSustainTable[inpGetMidiCtrl(cmd >> 0x18, sv->midi, sv->midiSet) >> 7];
            row = (s32*)(dataTables + (inpGetMidiCtrl((macCurrentCmd.para1 >> 8) & 0xff, sv->midi, sv->midiSet) >> 7) * 4);
            adsr.atime = row[7];
            row = (s32*)(dataTables + (inpGetMidiCtrl((macCurrentCmd.para1 >> 0x10) & 0xff, sv->midi, sv->midiSet) >> 7) * 4);
            adsr.dtime = row[7];
            adsr.slevel = 0xc1 - voiceAdsrDecayTable[fn_800F5C54(dlsScaleMax * sScale)];
            row = (s32*)(dataTables + (inpGetMidiCtrl((u8)*cmdValuePtr, sv->midi, sv->midiSet) >> 7) * 4);
            adsr.rtime = row[7];
            adsr.ascale = 0x80000000;
            adsr.dscale = 0x80000000;
            hwSetADSR(sv->id & 0xff, &adsr, 2);
            MAC_CFLAGS(sv) |= MAC_FLAG64(0, 0x100);
            break;
        }
        case 0x17:
            mcmdRandomKey(sv, &macCurrentCmd);
            break;
        case 0x18:
            if ((cmd >> 0x18) == 0) {
                sv->curNote += (s8)((cmd >> 8) & 0xff);
            } else {
                sv->curNote = sv->orgNote + (s8)((cmd >> 8) & 0xff);
            }
            sv->curNote = (s16)sv->curNote < 0 ? 0 : sv->curNote > 0x7f ? 0x7f : sv->curNote;
            sv->curDetune = (s8)(macCurrentCmd.para1 >> 0x10);
            if (voiceIsLastStarted(sv) != 0) {
                inpSetMidiLastNote(sv->midi, sv->midiSet, sv->curNote & 0xff);
            }
            macCurrentCmd.para1 = 4;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        case 0x19:
            sv->curNote = (cmd >> 8) & 0x7f;
            sv->curDetune = (s8)(macCurrentCmd.para1 >> 0x10);
            if (voiceIsLastStarted(sv) != 0) {
                inpSetMidiLastNote(sv->midi, sv->midiSet, sv->curNote & 0xff);
            }
            macCurrentCmd.para1 = 4;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        case 0x1a:
            sv->curNote = sv->lastNote + (s8)((cmd >> 8) & 0xff);
            sv->curNote = (s16)sv->curNote < 0 ? 0 : sv->curNote > 0x7f ? 0x7f : sv->curNote;
            sv->curDetune = (s8)(macCurrentCmd.para1 >> 0x10);
            if (sv->midi != 0xff) {
                inpSetMidiLastNote(sv->midi, sv->midiSet, sv->curNote & 0xff);
            }
            macCurrentCmd.para1 = 4;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        case 0x1b:
            mcmdPortamento(sv, &macCurrentCmd);
            break;
        case 0x1c:
            mcmdVibrato(sv, &macCurrentCmd);
            break;
        case 0x1d: {
            s32 result;
            sv->sweepOff[0] = 0;
            sv->sweepNum[0] = (macCurrentCmd.para1 >> 8) & 0xff;
            sv->sweepCnt[0] = sv->sweepNum[0] << 0x10;
            if ((result = (s16)(macCurrentCmd.para1 >> 0x10)) >= 0) {
                result = hwExitStream(result);
            } else {
                result = -hwExitStream(-result);
            }
            sv->sweepAdd[0] = result << 0x10;
            macCurrentCmd.para1 = 0;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        }
        case 0x1e: {
            s32 result;
            sv->sweepOff[1] = 0;
            sv->sweepNum[1] = (macCurrentCmd.para1 >> 8) & 0xff;
            sv->sweepCnt[1] = sv->sweepNum[1] << 0x10;
            if ((result = (s16)(macCurrentCmd.para1 >> 0x10)) >= 0) {
                result = hwExitStream(result);
            } else {
                result = -hwExitStream(-result);
            }
            sv->sweepAdd[1] = result << 0x10;
            macCurrentCmd.para1 = 0;
            ex = mcmdWait(sv, &macCurrentCmd);
            break;
        }
        case 0x1f:
            sv->playFrq = cmd >> 8;
            sv->playFrq |= (u8)*cmdValuePtr;
            if (sv->sInfo != 0xffffffff) {
                DoSetPitch(sv);
            }
            break;
        case 0x20:
            mcmdSetPitchADSR(sv, &macCurrentCmd);
            break;
        case 0x21: {
            u16 scale = (cmd >> 8) & 0xffff;
            if ((cmd >> 0x18) == 0) {
                sv->volume = ((sv->volume >> 5) * scale) >> 7;
            } else {
                sv->volume = ((sv->orgVolume >> 5) * scale) >> 7;
            }
            if (sv->volume > 0x7f0000) {
                sv->volume = 0x7f0000;
            }
            MAC_CFLAGS(sv) |= MAC_FLAG64(0x1000, 0);
            break;
        }
        case 0x22:
            sv->vibModAddScale = (s8)(cmd >> 8) << 8;
            if (sv->vibModAddScale >= 0) {
                sv->vibModAddScale += ((s16)(s8)(macCurrentCmd.para1 >> 0x10) << 8) / 100;
            } else {
                sv->vibModAddScale -= ((s16)(s8)(macCurrentCmd.para1 >> 0x10) << 8) / 100;
            }
            break;
        case 0x23:
            sv->treScale = (cmd >> 8) & 0xffff;
            sv->treModAddScale = *cmdValuePtr;
            sv->treCurScale = one;
            break;
        case 0x24:
            if (sv->callStackEntryNum != 0) {
                sv->addr = sv->callStack[sv->callStackIndex].addr;
                sv->curAddr = sv->callStack[sv->callStackIndex].curAddr;
                sv->callStackIndex = (sv->callStackIndex - 1) & 3;
                --sv->callStackEntryNum;
            }
            break;
        case 0x25: {
            u8* macro = dataGetMacro(cmd >> 0x10);
            u32 stop;
            if (macro != 0) {
                sv->callStackIndex = (sv->callStackIndex + 1) & 3;
                sv->callStack[sv->callStackIndex].addr = sv->addr;
                sv->callStack[sv->callStackIndex].curAddr = sv->curAddr;
                if (++sv->callStackEntryNum > 4) {
                    sv->callStackEntryNum = 4;
                }
                sv->addr = macro;
                stop = 0;
                sv->curAddr = macro + ((*cmdValuePtr & 0xffff) << 3);
            } else {
                vidRemoveVoiceReferences(sv);
                voiceFree(sv);
                stop = 1;
            }
            ex = stop;
            break;
        }
        case 0x28: {
            u8* macro = dataGetMacro(cmd >> 0x10);
            if (macro != 0) {
                u32 t = (macCurrentCmd.para1 >> 8) & 0xff;
                sv->trapEventAddr[t] = macro;
                sv->trapEventCurAddr[t] = macro + ((macCurrentCmd.para2 & 0xffff) << 3);
                sv->trapEventAny = 1;
                if (t == 0 && (MAC_CFLAGS(sv) & MAC_FLAG64(0x100, 8)) == MAC_FLAG64(0x100, 8)) {
                    MAC_CFLAGS(sv) |= MAC_FLAG64(0x400, 0);
                }
            }
            break;
        }
        case 0x29:
            mcmdUntrapEvent(sv, &macCurrentCmd);
            break;
        case 0x2a:
            mcmdSendMessage(sv, &macCurrentCmd);
            break;
        case 0x2b: {
            u32 mesg = 0;
            if (sv->mesgNum != 0) {
                mesg = sv->mesgQueue[sv->mesgRead];
                sv->mesgRead = (sv->mesgRead + 1) & 3;
                --sv->mesgNum;
            }
            varSet32(sv, 0, (macCurrentCmd.para1 >> 8) & 0xff, mesg);
            break;
        }
        case 0x2c:
            mcmdGetVID(sv, &macCurrentCmd);
            break;
        case 0x30: {
            s32 age = (sv->age >> 0xf) + (s16)(cmd >> 0x10);
            if (age < 0) {
                sv->age = 0;
            } else if (age > 0xffff) {
                sv->age = 0x7fff8000;
            } else {
                sv->age = age << 0xf;
            }
            hwSetPriority(sv->id & 0xff, ((u32)sv->prio << 0x18) | (sv->age >> 0xf));
            break;
        }
        case 0x31:
            sv->age = ((cmd >> 0x10) & 0xffff) << 0xf;
            hwSetPriority(sv->id & 0xff, ((u32)sv->prio << 0x18) | (sv->age >> 0xf));
            break;
        case 0x32:
            lbl_8061A504[(cmd >> 8) & 0xff] = (cmd >> 0x10) & 0xff;
            break;
        case 0x33:
            sv->pbLowerKeyRange = (cmd >> 0x10) & 0xff;
            sv->pbUpperKeyRange = (macCurrentCmd.para1 >> 8) & 0xff;
            break;
        case 0x34:
            sv->revVolScale = (cmd >> 8) & 0xff;
            sv->revVolOffset = (macCurrentCmd.para1 >> 0x10) & 0xff;
            break;
        case 0x35:
            MAC_CFLAGS(sv) |= MAC_FLAG64(0, 0x10000);
            break;
        case 0x36:
            voiceSetPriority(sv, (cmd >> 8) & 0xff);
            break;
        case 0x37:
            mcmdAddPriority(sv, &macCurrentCmd);
            break;
        case 0x38:
            if (*cmdValuePtr != 0) {
                sv->ageSpeed = (sv->age >> 8) / *cmdValuePtr;
            } else {
                sv->ageSpeed = 0;
            }
            break;
        case 0x39:
            mcmdSetAgeCounterByVolume(sv, &macCurrentCmd);
            break;
        case 0x40:
            SelectSource(sv, &sv->inpVolume, &macCurrentCmd, MAC_FLAG64(0, 0x80000), 1);
            break;
        case 0x41:
            SelectSource(sv, &sv->inpPanning, &macCurrentCmd, MAC_FLAG64(0, 0x100000), 2);
            break;
        case 0x42:
            SelectSource(sv, &sv->inpPitchBend, &macCurrentCmd, MAC_FLAG64(0, 0x200000), 8);
            break;
        case 0x43:
            SelectSource(sv, &sv->inpModulation, &macCurrentCmd, MAC_FLAG64(0, 0x400000), 0x20);
            break;
        case 0x44:
            SelectSource(sv, &sv->inpPedal, &macCurrentCmd, MAC_FLAG64(0, 0x2000000), 0x40);
            break;
        case 0x45:
            SelectSource(sv, &sv->inpPortamento, &macCurrentCmd, MAC_FLAG64(0, 0x1000000), 0x80);
            break;
        case 0x46:
            SelectSource(sv, &sv->inpReverb, &macCurrentCmd, MAC_FLAG64(0, 0x800000), 0x200);
            break;
        case 0x47:
            SelectSource(sv, &sv->inpSurroundPanning, &macCurrentCmd, MAC_FLAG64(0, 0x4000000), 4);
            break;
        case 0x48:
            SelectSource(sv, &sv->inpDoppler, &macCurrentCmd, MAC_FLAG64(0, 0x8000000), 0x10);
            break;
        case 0x49:
            SelectSource(sv, &sv->inpTremolo, &macCurrentCmd, MAC_FLAG64(0, 0x10000000), 0x1000);
            break;
        case 0x4a:
            SelectSource(sv, &sv->inpPreAuxA, &macCurrentCmd, MAC_FLAG64(0, 0x20000000), 0x100);
            break;
        case 0x4b:
            SelectSource(sv, &sv->inpPreAuxB, &macCurrentCmd, MAC_FLAG64(0, 0x40000000), 0x400);
            break;
        case 0x4c:
            SelectSource(sv, &sv->inpPostAuxB, &macCurrentCmd, MAC_FLAG64(0, 0x80000000), 0x800);
            break;
        case 0x4d: {
            u8 i = *cmdValuePtr >> 0x18;
            u64* mask = (u64*)(dataTables + i * 8);
            u32* dirty = (u32*)(dataTables + i * 4);
            SelectSource(sv, (INPUT_SLOT*)((u8*)inpAuxA + sv->studio * 0x90 + i * 0x24), &macCurrentCmd, mask[68], dirty[144]);
            break;
        }
        case 0x4e: {
            u8 i = *cmdValuePtr >> 0x18;
            u64* mask = (u64*)(dataTables + i * 8);
            u32* dirty = (u32*)(dataTables + i * 4);
            SelectSource(sv, (INPUT_SLOT*)((u8*)inpAuxB + sv->studio * 0x90 + i * 0x24), &macCurrentCmd, mask[74], dirty[156]);
            break;
        }
        case 0x50: {
            u32 unused2;
            u32 phase;
            u32 time;
            u8 controllerIndex;

            controllerIndex = (u8)(macCurrentCmd.para1 >> 8);
            time = (u16)(macCurrentCmd.para1 >> 0x10);
            sndConvertMs(&time);
            if (sv->lfo[controllerIndex].period != 0) {
                phase = (u16)macCurrentCmd.para2;
                sndConvertMs(&phase);
                sv->lfo[controllerIndex].time = phase;
            }
            sv->lfo[controllerIndex].period = time;
            break;
        }
        case 0x58:
            sv->volTable = ((cmd >> 8) & 0xff) != 0 ? 1 : 0;
            sv->itdMode = ((macCurrentCmd.para1 >> 0x10) & 0xff) != 0 ? 0 : 1;
            break;
        case 0x59:
            mcmdSetKeyGroup(sv, &macCurrentCmd);
            break;
        case 0x5a:
            mcmdSRCModeSelect(sv, &macCurrentCmd);
            break;
        case 0x60:
            mcmdVarCalculation(sv, &macCurrentCmd, 0);
            break;
        case 0x61:
            mcmdVarCalculation(sv, &macCurrentCmd, 1);
            break;
        case 0x62:
            mcmdVarCalculation(sv, &macCurrentCmd, 2);
            break;
        case 0x63:
            mcmdVarCalculation(sv, &macCurrentCmd, 3);
            break;
        case 0x64:
            mcmdVarCalculation(sv, &macCurrentCmd, 4);
            break;
        case 0x65: {
            u8 ctrl = (cmd >> 8) & 0xff;
            u8 index = (cmd >> 0x10) & 0xff;
            u32 unused3[3];
            varSet32(sv, ctrl, index, (s16)*cmdValuePtr);
            break;
        }
        case 0x70:
            mcmdIfVarCompare(sv, &macCurrentCmd, 0);
            break;
        case 0x71:
            mcmdIfVarCompare(sv, &macCurrentCmd, 1);
            break;
        }
    } while (ex == 0);
}
