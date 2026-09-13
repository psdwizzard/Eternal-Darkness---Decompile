typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct _PBMIX {
    u16 vL, vDeltaL, vR, vDeltaR;
    u16 vAuxAL, vDeltaAuxAL, vAuxAR, vDeltaAuxAR;
    u16 vAuxBL, vDeltaAuxBL, vAuxBR, vDeltaAuxBR;
    u16 vAuxBS, vDeltaAuxBS, vS, vDeltaS, vAuxAS, vDeltaAuxAS;
} _PBMIX;
typedef struct _PBITD {
    u16 flag, bufferHi, bufferLo, shiftL, shiftR, targetShiftL, targetShiftR;
} _PBITD;
typedef struct _PBUPDATE {
    u16 updNum[5];
    u16 dataHi, dataLo;
} _PBUPDATE;
typedef struct _PBDPOP {
    u16 aL, aAuxAL, aAuxBL, aR, aAuxAR, aAuxBR, aS, aAuxAS, aAuxBS;
} _PBDPOP;
typedef struct _PBVE {
    u16 currentVolume, currentDelta;
} _PBVE;
typedef struct _PBFIR {
    u16 numCoefs, coefsHi, coefsLo;
} _PBFIR;
typedef struct _PBADDR {
    u16 loopFlag, format, loopAddressHi, loopAddressLo;
    u16 endAddressHi, endAddressLo, currentAddressHi, currentAddressLo;
} _PBADDR;
typedef struct _PBADPCM {
    u16 a[8][2];
    u16 gain, pred_scale, yn1, yn2;
} _PBADPCM;
typedef struct _PBSRC {
    u16 ratioHi, ratioLo, currentAddressFrac;
    u16 last_samples[4];
} _PBSRC;
typedef struct _PBADPCMLOOP {
    u16 loop_pred_scale, loop_yn1, loop_yn2;
} _PBADPCMLOOP;
typedef struct _PB {
    u16 nextHi;
    u16 nextLo;
    u16 currHi;
    u16 currLo;
    u16 srcSelect;
    u16 coefSelect;
    u16 mixerCtrl;
    u16 state;
    u16 loopType;
    _PBMIX mix;
    _PBITD itd;
    _PBUPDATE update;
    _PBDPOP dpop;
    _PBVE ve;
    _PBFIR fir;
    _PBADDR addr;
    _PBADPCM adpcm;
    _PBSRC src;
    _PBADPCMLOOP adpcmLoop;
    u16 streamLoopCnt;
} _PB;
typedef struct _SPB {
    u16 dpopLHi, dpopLLo, dpopLDelta;
    u16 dpopRHi, dpopRLo, dpopRDelta;
    u16 dpopSHi, dpopSLo, dpopSDelta;
    u16 dpopALHi, dpopALLo, dpopALDelta;
    u16 dpopARHi, dpopARLo, dpopARDelta;
    u16 dpopASHi, dpopASLo, dpopASDelta;
    u16 dpopBLHi, dpopBLLo, dpopBLDelta;
    u16 dpopBRHi, dpopBRLo, dpopBRDelta;
    u16 dpopBSHi, dpopBSLo, dpopBSDelta;
} _SPB;
typedef struct SNDADPCMinfo {
    u16 unk0;
    u8 initialPS;
    u8 loopPS;
    u16 loopY0;
    u16 loopY1;
    u16 coefTab[8][2];
} SNDADPCMinfo;
typedef struct DSPADPCMplusBlk {
    u16 Y0;
    u16 Y1;
    u8 PS;
    u8 pad5;
} DSPADPCMplusBlk;
typedef struct DSPADPCMplusInfo {
    u16 unk0;
    u8 initialPS;
    u8 loopPS;
    u16 loopY0;
    u16 loopY1;
    u16 coefTab[8][2];
    DSPADPCMplusBlk blk[1];
} DSPADPCMplusInfo;
typedef struct SAMPLE_INFO {
    u32 info;
    void* addr;
    void* extraData;
    u32 offset;
    u32 length;
    u32 loop;
    u32 loopLength;
    u8 compType;
    u8 pad1D[3];
} SAMPLE_INFO;
typedef struct VSampleInfo {
    void* loopBufferAddr;
    u32 loopBufferLength;
    u8 inLoopBuffer;
    u8 pad09[3];
} VSampleInfo;
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
typedef struct DSPvoice {
    _PB* pb;
    void* patchData;
    void* itdBuffer;
    struct DSPvoice* next;
    struct DSPvoice* prev;
    struct DSPvoice* nextAlien;
    u32 mesgCallBackUserValue;
    u32 prio;
    u32 currentAddr;
    u32 changed[5];
    u32 pitch[5];
    u16 volL;
    u16 volR;
    u16 volS;
    u16 volLa;
    u16 volRa;
    u16 volSa;
    u16 volLb;
    u16 volRb;
    u16 volSb;
    u16 lastVolL;
    u16 lastVolR;
    u16 lastVolS;
    u16 lastVolLa;
    u16 lastVolRa;
    u16 lastVolSa;
    u16 lastVolLb;
    u16 lastVolRb;
    u16 lastVolSb;
    u16 smp_id;
    u8 pad72[2];
    SAMPLE_INFO smp_info;
    VSampleInfo vSampleInfo;
    u8 streamLoopPS;
    u8 padA1[3];
    ADSR_VARS adsr;
    u16 srcTypeSelect;
    u16 srcCoefSelect;
    u16 itdShiftL;
    u16 itdShiftR;
    u8 singleOffset;
    u8 padD5[3];
    struct {
        u32 posHi;
        u32 posLo;
        u32 pitch;
    } playInfo;
    u8 lastUpdate[4];
    u32 virtualSampleID;
    u8 state;
    u8 postBreak;
    u8 startupBreak;
    u8 studio;
    u32 flags;
} DSPvoice;
typedef struct DSPhostDPop {
    s32 l, r, s, lA, rA, sA, lB, rB, sB;
} DSPhostDPop;
typedef struct DSPinput {
    u8 studio;
    u8 pad01;
    u16 vol;
    u16 volA;
    u16 volB;
    void* desc;
} DSPinput;
typedef struct DSPstudioinfo {
    _SPB* spb;
    DSPhostDPop hostDPopSum;
    s32* main[2];
    s32* auxA[3];
    s32* auxB[3];
    DSPvoice* voiceRoot;
    DSPvoice* alienVoiceRoot;
    u8 state;
    u8 isMaster;
    u8 numInputs;
    u8 pad53;
    s32 type;
    DSPinput in[7];
    void* auxAHandler;
    void* auxBHandler;
    void* auxAUser;
    void* auxBUser;
} DSPstudioinfo;

static DSPstudioinfo dspStudio[8];
static DSPvoice* voices[64];

extern u16* lbl_8064D498;
extern u32 lbl_8064D49C;
extern u16* lbl_8064D490;
extern u16* lbl_8064D48C;
extern u16* lbl_8064D488;
extern u16* lbl_8064D47C;
extern u16* lbl_8064D480;
extern u16 lbl_8064D484;
extern u16 lbl_8064D494;
extern u8 lbl_8064D4E7;
extern u8 lbl_8064D4E6;
extern u8 lbl_8064D4E4;
extern u32 lbl_8064D478;
extern void* lbl_8064D4A4;
extern u16 lbl_8023B2F0[];
extern u16 lbl_80253130[4][3];
extern u16 lbl_8023B330[];

extern void fn_801C47A8(DSPstudioinfo*, DSPvoice*);
extern int fn_801C753C(DSPvoice*, int);
extern void fn_801C7624(DSPvoice*);
extern void fn_8020B7D8(void*, u32);
extern void fn_801C4A60(DSPvoice**, s32, s32);
extern u32 fn_801C2D74(ADSR_VARS*);
extern u32 fn_801C46B4(u16*, u16*, u16*, u16, u16*, u16);
extern int fn_801C2EF0(ADSR_VARS*);
extern u32 fn_801C2F34(ADSR_VARS*, u16*, u16*);
extern int fn_801C2D9C(ADSR_VARS*, u32);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void DCFlushRangeNoSync(void*, u32);

#define dspCmdList lbl_8064D498
#define dspHRTFOn lbl_8064D49C
#define dspCmdPtr lbl_8064D490
#define dspCmdMaxPtr lbl_8064D48C
#define dspCmdCurBase lbl_8064D488
#define dspCmdLastLoad lbl_8064D47C
#define dspCmdLastBase lbl_8064D480
#define dspCmdLastSize lbl_8064D484
#define dspCmdFirstSize lbl_8064D494
#define salFrame lbl_8064D4E7
#define salAuxFrame lbl_8064D4E6
#define salMaxStudioNum lbl_8064D4E4
#define dspARAMZeroBuffer lbl_8064D478
#define dspSurround lbl_8064D4A4
#define dspMixerCycles lbl_8023B2F0
#define pbOffsets lbl_8023B330
#define dspSRCCycles lbl_80253130
u32 __OSBusClock : 0x800000F8;
#define OS_BUS_CLOCK __OSBusClock
#define HandleDepopVoice fn_801C47A8
#define salSynthSendMessage fn_801C753C
#define salDeactivateVoice fn_801C7624
#define DCStoreRangeNoSync fn_8020B7D8
#define SortVoices fn_801C4A60
#define adsrSetup fn_801C2D74
#define salCheckVolErrorAndResetDelta fn_801C46B4
#define adsrRelease fn_801C2EF0
#define adsrHandle fn_801C2F34
#define adsrStartRelease fn_801C2D9C
#define DSP_VOICE_CHANGE_ADSR 0x10
#define DSP_VOICE_CHANGE_BREAK 0x20
#define DSP_VOICE_CHANGE_KEYOFF 0x40
#define DSP_VOICE_CHANGE_POLYPHASE 0x80
#define DSP_VOICE_CHANGE_SRC_TYPE 0x100
#define DSP_VOICE_CHANGE_ITD 0x200
#define DSP_VOICE_STATE_INACTIVE 0
#define DSP_VOICE_STATE_STARTUP 1
#define DSP_VOICE_STATE_ACTIVE 2
#define DSP_STUDIO_STATE_ACTIVE 1
#define SND_STUDIO_TYPE_STD 0

static inline void sal_setup_dspvol(u16* dsp_delta, u16* last_vol, u16 vol)
{
    *dsp_delta = ((s16)vol - (s16)*last_vol) / 160;
    *last_vol += (s16)*dsp_delta * 160;
}

static inline void sal_update_hostplayinfo(DSPvoice* dsp_vptr)
{
    u32 old_lo;
    u32 pitch;

    if (dsp_vptr->smp_info.loopLength != 0) {
        return;
    }
    if (dsp_vptr->pb->srcSelect != 2) {
        pitch = dsp_vptr->playInfo.pitch << 5;
    } else {
        pitch = 0x200000;
    }
    old_lo = dsp_vptr->playInfo.posLo;
    dsp_vptr->playInfo.posLo += pitch * 0x10000;
    if (old_lo > dsp_vptr->playInfo.posLo) {
        dsp_vptr->playInfo.posHi += (pitch >> 16) + 1;
    } else {
        dsp_vptr->playInfo.posHi += (pitch >> 16);
    }
}

static inline void DoDepopFade(s32* dspStart, s16* dspDelta, s32* hostSum)
{
    if (*hostSum <= -160) {
        *dspDelta = (*hostSum <= -3200) ? 0x14 : (s16)(-*hostSum / 160);
    } else if (*hostSum >= 160) {
        *dspDelta = (*hostSum >= 3200) ? -0x14 : (s16)(-*hostSum / 160);
    } else {
        *dspDelta = 0;
    }
    *dspStart = *hostSum;
    *hostSum += *dspDelta * 160;
}

#define SAL_CHECK_CMD_SPACE(n)                                                                 \
    if ((dspCmdPtr + (n)) > (dspCmdMaxPtr - 4)) {                                              \
        u16 size;                                                                              \
        dspCmdPtr[0] = 13;                                                                     \
        dspCmdPtr[1] = (u32)dspCmdMaxPtr >> 16;                                                \
        dspCmdPtr[2] = (u32)dspCmdMaxPtr;                                                      \
        size = (((u32)(dspCmdPtr + 4) - (u32)dspCmdCurBase) + 3) & 0xFFFC;                     \
        if (dspCmdLastLoad) {                                                                  \
            dspCmdLastLoad[3] = size;                                                          \
            DCStoreRangeNoSync(dspCmdLastBase, dspCmdLastSize);                                \
        } else {                                                                               \
            dspCmdFirstSize = size;                                                            \
        }                                                                                      \
        dspCmdLastLoad = dspCmdPtr;                                                            \
        dspCmdLastSize = size;                                                                 \
        dspCmdLastBase = dspCmdCurBase;                                                        \
        dspCmdCurBase = dspCmdPtr = dspCmdMaxPtr;                                              \
        dspCmdMaxPtr = dspCmdPtr + 0xC0;                                                       \
    }

void fn_801C4B5C(s16* dest, u32 nsDelay)
{
    u8 s;
    u8 mix_start;
    u8 st;
    u8 st1;
    u8 getAuxFrame;
    u16 rampResetOffsetFlags[5];
    DSPstudioinfo* stp;
    DSPvoice* dsp_vptr;
    DSPvoice* next_dsp_vptr;
    u32 tmp_addr;
    u32 addr;
    u32 base;
    u32 in;
    u32 voiceNum;
    u32 cyclesUsed;
    u16* pptr;
    u16* pend;
    u16 adsr_start;
    u16 adsr_delta;
    u16 old_adsr_delta;
    s32 current_delta;
    s32 voiceIdx;
    _PB* pb;
    _PB* last_pb;
    u32 VoiceDone;
    u32 needsDelta;
    u32 newVoice;
    _SPB* spb;
    u32 procVoiceFlag;
    u32 offset;
    u32 endAddr;
    u32 loopAddr;
    u32 zeroAddr;
    DSPvoice* nextVoice;

    dspCmdCurBase = dspCmdPtr = dspCmdList;
    dspCmdMaxPtr = dspCmdPtr + 0xC0;
    dspCmdLastLoad = 0;
    cyclesUsed = 10430;
    if (dspHRTFOn != 0)
    {
        cyclesUsed += 45000;
    }
    rampResetOffsetFlags[0] = 0;
    for (st = 0; st < salMaxStudioNum; st++)
    {
        if (dspStudio[st].state == DSP_STUDIO_STATE_ACTIVE)
        {
            stp = &dspStudio[st];
            for (dsp_vptr = stp->voiceRoot; dsp_vptr; dsp_vptr = next_dsp_vptr)
            {
                next_dsp_vptr = dsp_vptr->next;
                if ((dsp_vptr->postBreak != 0) || ((dsp_vptr->changed[0] & DSP_VOICE_CHANGE_BREAK) != 0))
                {
                    HandleDepopVoice(stp, dsp_vptr);
                    if (dsp_vptr->virtualSampleID != -1)
                    {
                        salSynthSendMessage(dsp_vptr, 3);
                    }
                    if ((dsp_vptr->state != DSP_VOICE_STATE_STARTUP) || (dsp_vptr->startupBreak != 0))
                    {
                        salDeactivateVoice(dsp_vptr);
                        dsp_vptr->startupBreak = 0;
                    }
                }
            }
            for (dsp_vptr = stp->alienVoiceRoot; dsp_vptr; dsp_vptr = dsp_vptr->nextAlien)
            {
                HandleDepopVoice(stp, dsp_vptr);
            }
            stp->alienVoiceRoot = 0;
            SAL_CHECK_CMD_SPACE(3);
            dspCmdPtr[0] = 0;
            cyclesUsed += 0x2C62;
            dspCmdPtr[1] = (u32)stp->spb >> 16;
            dspCmdPtr[2] = (u32)stp->spb;
            dspCmdPtr += 3;
            for (in = 0; in < stp->numInputs; in++)
            {
                SAL_CHECK_CMD_SPACE(6);
                dspCmdPtr[0] = 1;
                dspCmdPtr[1] = (u32)dspStudio[stp->in[in].studio].main[salFrame ^ 1] >> 16;
                dspCmdPtr[2] = (u32)dspStudio[stp->in[in].studio].main[salFrame ^ 1];
                dspCmdPtr[3] = stp->in[in].vol;
                dspCmdPtr[4] = stp->in[in].volA;
                dspCmdPtr[5] = stp->in[in].volB;
                dspCmdPtr += 6;
                cyclesUsed += 0x294D;
            }
            last_pb = 0;
            for (voiceIdx = 0, dsp_vptr = stp->voiceRoot; dsp_vptr;
                 voiceIdx++, dsp_vptr = nextVoice)
            {
                voices[voiceIdx] = dsp_vptr;
                nextVoice = dsp_vptr->next;
            }
            voiceNum = voiceIdx;
            SortVoices(voices, 0, voiceNum - 1);
            procVoiceFlag = 0;
            for (voiceIdx = voiceNum; voiceIdx > 0; voiceIdx--)
            {
                dsp_vptr = voices[voiceIdx - 1];
                if (dsp_vptr->state != DSP_VOICE_STATE_INACTIVE)
                {
                    u8 i;
                    pb = dsp_vptr->pb;
                    for (s = 1; s < 5; s++)
                    {
                        rampResetOffsetFlags[s] = 0;
                    }
                    if (dsp_vptr->state == DSP_VOICE_STATE_STARTUP)
                    {
                        dsp_vptr->virtualSampleID = -1;
                        dsp_vptr->pb->ve.currentDelta = 0x8000;
                        if (adsrSetup(&dsp_vptr->adsr) != 0)
                        {
                            salSynthSendMessage(dsp_vptr, 0);
                            salDeactivateVoice(dsp_vptr);
                            continue;
                        }
                        dsp_vptr->virtualSampleID = -1;
                        switch (dsp_vptr->smp_info.compType)
                        {
                        case 5:
                            dsp_vptr->vSampleInfo.loopBufferLength = 0;
                            dsp_vptr->virtualSampleID = salSynthSendMessage(dsp_vptr, 2);
                            if (dsp_vptr->vSampleInfo.loopBufferLength == 0)
                            {
                                salSynthSendMessage(dsp_vptr, 1);
                                salDeactivateVoice(dsp_vptr);
                                continue;
                            }
                            break;
                        }
                        pb->src.currentAddressFrac = 0;
                        pb->src.last_samples[0] = 0;
                        pb->src.last_samples[1] = 0;
                        pb->src.last_samples[2] = 0;
                        pb->src.last_samples[3] = 0;
                        if ((dsp_vptr->flags & 0x80000000) != 0)
                        {
                            memset(dsp_vptr->itdBuffer, 0, 0x40);
                            DCFlushRange(dsp_vptr->itdBuffer, 0x40);
                            pb->itd.targetShiftL = dsp_vptr->itdShiftL;
                            pb->itd.shiftL = dsp_vptr->itdShiftL;
                            pb->itd.targetShiftR = dsp_vptr->itdShiftR;
                            pb->itd.shiftR = dsp_vptr->itdShiftR;
                            pb->itd.flag = 1;
                        }
                        else
                        {
                            pb->itd.flag = 0;
                        }
                        switch (dsp_vptr->smp_info.compType)
                        {
                        case 0:
                        case 4:
                        case 5:
                        {
                            SNDADPCMinfo* adpcmInfo;
                            pb->addr.format = 0;
                            pb->adpcm.gain = 0;
                            adpcmInfo = dsp_vptr->smp_info.extraData;
                            pb->adpcm.yn2 = 0;
                            pb->adpcm.yn1 = 0;
                            pb->adpcm.pred_scale = adpcmInfo->initialPS;
                            for (i = 0; i < 8; i++)
                            {
                                pb->adpcm.a[i][0] = adpcmInfo->coefTab[i][0];
                                pb->adpcm.a[i][1] = adpcmInfo->coefTab[i][1];
                            }
                            addr = (base = (u32)dsp_vptr->smp_info.addr * 2) + 2;
                            dsp_vptr->playInfo.posHi = dsp_vptr->playInfo.posLo = 0;
                            if ((dsp_vptr->smp_info.compType == 4) || (dsp_vptr->smp_info.compType == 5))
                            {
                                pb->loopType = 1;
                            }
                            else
                            {
                                pb->adpcmLoop.loop_yn2 = adpcmInfo->loopY0;
                                pb->adpcmLoop.loop_yn1 = adpcmInfo->loopY1;
                                pb->adpcmLoop.loop_pred_scale = adpcmInfo->loopPS;
                                pb->loopType = 0;
                            }
                        }
                        break;
                        case 1:
                        {
                            DSPADPCMplusInfo* adpcmInfo;
                            pb->addr.format = 0;
                            pb->adpcm.gain = 0;
                            offset = (dsp_vptr->smp_info.offset + 0xD) / 14;
                            adpcmInfo = dsp_vptr->smp_info.extraData;
                            pb->adpcm.yn2 = adpcmInfo->blk[offset].Y0;
                            pb->adpcm.yn1 = adpcmInfo->blk[offset].Y1;
                            pb->adpcm.pred_scale = adpcmInfo->blk[offset].PS;
                            pb->adpcmLoop.loop_yn2 = adpcmInfo->loopY0;
                            pb->adpcmLoop.loop_yn1 = adpcmInfo->loopY1;
                            pb->adpcmLoop.loop_pred_scale = adpcmInfo->loopPS;
                            for (i = 0; i < 8; i++)
                            {
                                pb->adpcm.a[i][0] = adpcmInfo->coefTab[i][0];
                                pb->adpcm.a[i][1] = adpcmInfo->coefTab[i][1];
                            }
                            addr = (base = (u32)dsp_vptr->smp_info.addr * 2) + offset * 16 + 2;
                            dsp_vptr->playInfo.posHi = offset * 0xE;
                            dsp_vptr->playInfo.posLo = 0;
                        }
                        break;
                        case 3:
                        {
                            pb->addr.format = 0x19;
                            pb->adpcm.gain = 0x100;
                            for (i = 0; i < 8; i++)
                            {
                                pb->adpcm.a[i][0] = 0;
                                pb->adpcm.a[i][1] = 0;
                            }
                            addr = dsp_vptr->smp_info.offset + (base = (u32)dsp_vptr->smp_info.addr);
                            dsp_vptr->playInfo.posHi = dsp_vptr->smp_info.offset;
                            dsp_vptr->playInfo.posLo = 0;
                        }
                        break;
                        case 2:
                        {
                            pb->addr.format = 0xA;
                            pb->adpcm.gain = 0x800;
                            for (i = 0; i < 8; i++)
                            {
                                pb->adpcm.a[i][0] = 0;
                                pb->adpcm.a[i][1] = 0;
                            }
                            addr = dsp_vptr->smp_info.offset + (base = (u32)dsp_vptr->smp_info.addr >> 1);
                            dsp_vptr->playInfo.posHi = dsp_vptr->smp_info.offset;
                            dsp_vptr->playInfo.posLo = 0;
                        }
                        break;
                        }
                        pb->addr.currentAddressHi = addr >> 0x10;
                        pb->addr.currentAddressLo = addr;
                        dsp_vptr->currentAddr = addr;
                        if (dsp_vptr->smp_info.loopLength != 0)
                        {
                            pb->addr.loopFlag = 1;
                            switch (dsp_vptr->smp_info.compType)
                            {
                            case 0:
                            case 1:
                            case 4:
                            {
                                u32 bn;
                                u32 bo;
                                bn = dsp_vptr->smp_info.loop / 14;
                                bo = dsp_vptr->smp_info.loop - (bn * 0xE);
                                loopAddr = base + bn * 16 + 2 + bo;
                                endAddr = dsp_vptr->smp_info.loop + dsp_vptr->smp_info.loopLength - 1;
                                bn = endAddr / 14;
                                bo = endAddr - (bn * 0xE);
                                endAddr = base + bn * 16 + 2 + bo;
                            }
                            break;
                            case 5:
                            {
                                u32 bn;
                                u32 bo;
                                loopAddr = ((u32)dsp_vptr->vSampleInfo.loopBufferAddr * 2) + 2;
                                endAddr = dsp_vptr->smp_info.loop + dsp_vptr->smp_info.loopLength - 1;
                                bn = endAddr / 14;
                                bo = endAddr - (bn * 0xE);
                                endAddr = base + bn * 16 + 2 + bo;
                                dsp_vptr->vSampleInfo.inLoopBuffer = 0;
                            }
                            break;
                            case 2:
                            case 3:
                            default:
                                loopAddr = base + dsp_vptr->smp_info.loop;
                                endAddr = base + dsp_vptr->smp_info.loop + dsp_vptr->smp_info.loopLength - 1;
                                break;
                            }
                            pb->addr.loopAddressHi = loopAddr >> 16;
                            pb->addr.loopAddressLo = loopAddr;
                            pb->addr.endAddressHi = endAddr >> 16;
                            pb->addr.endAddressLo = endAddr;
                            pb->streamLoopCnt = 0;
                        }
                        else
                        {
                            pb->addr.loopFlag = 0;
                            switch (dsp_vptr->smp_info.compType)
                            {
                            case 0:
                            case 1:
                            case 4:
                            case 5:
                            {
                                u32 bn;
                                u32 bo;
                                bn = dsp_vptr->smp_info.length / 14;
                                bo = dsp_vptr->smp_info.length - (bn * 0xE);
                                tmp_addr = base + bn * 16 + 2 + bo;
                                zeroAddr = (dspARAMZeroBuffer * 2) + 2;
                            }
                            break;
                            case 3:
                                tmp_addr = base + dsp_vptr->smp_info.length;
                                zeroAddr = dspARAMZeroBuffer;
                                break;
                            case 2:
                                tmp_addr = base + dsp_vptr->smp_info.length;
                                zeroAddr = dspARAMZeroBuffer >> 1;
                                break;
                            }
                            pb->addr.loopAddressHi = zeroAddr >> 16;
                            pb->addr.loopAddressLo = zeroAddr;
                            pb->addr.endAddressHi = tmp_addr >> 16;
                            pb->addr.endAddressLo = tmp_addr;
                        }
                        pb->srcSelect = dsp_vptr->srcTypeSelect;
                        pb->coefSelect = dsp_vptr->srcCoefSelect;
                        pb->state = (mix_start = dsp_vptr->singleOffset) ? 0 : 1;
                        pb->mix.vL = dsp_vptr->lastVolL = dsp_vptr->volL;
                        pb->mix.vR = dsp_vptr->lastVolR = dsp_vptr->volR;
                        pb->mix.vS = dsp_vptr->lastVolS = dsp_vptr->volS;
                        pb->mix.vAuxAL = dsp_vptr->lastVolLa = dsp_vptr->volLa;
                        pb->mix.vAuxAR = dsp_vptr->lastVolRa = dsp_vptr->volRa;
                        pb->mix.vAuxAS = dsp_vptr->lastVolSa = dsp_vptr->volSa;
                        pb->mixerCtrl = (pb->mix.vAuxAS | (pb->mix.vAuxAL | pb->mix.vAuxAR)) != 0 ? 1 : 0;
                        pb->mix.vAuxBL = dsp_vptr->lastVolLb = dsp_vptr->volLb;
                        pb->mix.vAuxBR = dsp_vptr->lastVolRb = dsp_vptr->volRb;
                        pb->mix.vAuxBS = dsp_vptr->lastVolSb = dsp_vptr->volSb;
                        pb->mix.vDeltaL = 0;
                        pb->mix.vDeltaR = 0;
                        pb->mix.vDeltaS = 0;
                        pb->mix.vDeltaAuxAL = 0;
                        pb->mix.vDeltaAuxAR = 0;
                        pb->mix.vDeltaAuxAS = 0;
                        pb->mix.vDeltaAuxBL = 0;
                        pb->mix.vDeltaAuxBR = 0;
                        pb->mix.vDeltaAuxBS = 0;
                        if (stp->type == SND_STUDIO_TYPE_STD)
                        {
                            if ((pb->mix.vAuxBS | (pb->mix.vAuxBL | pb->mix.vAuxBR)) != 0)
                            {
                                pb->mixerCtrl |= 2;
                            }
                            if ((pb->mix.vAuxBS | (pb->mix.vS | pb->mix.vAuxAS)) != 0)
                            {
                                pb->mixerCtrl |= 4;
                            }
                        }
                        else if ((pb->mix.vAuxAS | (pb->mix.vAuxBL | pb->mix.vAuxBR)) != 0)
                        {
                            pb->mixerCtrl |= 0x10;
                        }
                        dsp_vptr->state = DSP_VOICE_STATE_ACTIVE;
                        newVoice = 1;
                    }
                    else
                    {
                        if ((dsp_vptr->smp_info.compType == 4) || (dsp_vptr->smp_info.compType == 5))
                        {
                            pb->adpcmLoop.loop_pred_scale = dsp_vptr->streamLoopPS;
                            if ((dsp_vptr->smp_info.compType == 5) && (dsp_vptr->vSampleInfo.inLoopBuffer == 0) &&
                                (pb->streamLoopCnt != 0))
                            {
                                u32 bn;
                                u32 bo;
                                bn = (dsp_vptr->vSampleInfo.loopBufferLength - 1) / 14;
                                bo = (dsp_vptr->vSampleInfo.loopBufferLength - 1) - (bn * 14);
                                tmp_addr = ((u32)dsp_vptr->vSampleInfo.loopBufferAddr * 2) + bn * 16 + 2 + bo;
                                dsp_vptr->smp_info.addr = dsp_vptr->vSampleInfo.loopBufferAddr;
                                pb->addr.endAddressHi = tmp_addr >> 0x10;
                                pb->addr.endAddressLo = tmp_addr;
                                dsp_vptr->vSampleInfo.inLoopBuffer = 1;
                            }
                        }
                        if ((dsp_vptr->smp_info.loopLength == 0) && (dsp_vptr->playInfo.posHi >= dsp_vptr->smp_info.length))
                        {
                            salSynthSendMessage(dsp_vptr, 0);
                            salDeactivateVoice(dsp_vptr);
                            continue;
                        }
                        if (((dsp_vptr->changed[0] & DSP_VOICE_CHANGE_ADSR) != 0) &&
                            (adsrSetup(&dsp_vptr->adsr) != 0))
                        {
                            salSynthSendMessage(dsp_vptr, 0);
                            salDeactivateVoice(dsp_vptr);
                            continue;
                        }
                        if ((dsp_vptr->changed[0] & 1) != 0)
                        {
                            sal_setup_dspvol(&pb->mix.vDeltaL, &dsp_vptr->lastVolL, dsp_vptr->volL);
                            sal_setup_dspvol(&pb->mix.vDeltaR, &dsp_vptr->lastVolR, dsp_vptr->volR);
                            sal_setup_dspvol(&pb->mix.vDeltaS, &dsp_vptr->lastVolS, dsp_vptr->volS);
                            needsDelta = 1;
                        }
                        else
                        {
                            needsDelta = salCheckVolErrorAndResetDelta(&pb->mix.vL, &pb->mix.vDeltaL, &dsp_vptr->lastVolL,
                                                                       dsp_vptr->volL, rampResetOffsetFlags, 1);
                            needsDelta |= salCheckVolErrorAndResetDelta(&pb->mix.vR, &pb->mix.vDeltaR, &dsp_vptr->lastVolR,
                                                                        dsp_vptr->volR, rampResetOffsetFlags, 2);
                            needsDelta |= salCheckVolErrorAndResetDelta(&pb->mix.vS, &pb->mix.vDeltaS, &dsp_vptr->lastVolS,
                                                                        dsp_vptr->volS, rampResetOffsetFlags, 4);
                        }
                        if ((dsp_vptr->changed[0] & 2) != 0)
                        {
                            sal_setup_dspvol(&pb->mix.vDeltaAuxAL, &dsp_vptr->lastVolLa, dsp_vptr->volLa);
                            sal_setup_dspvol(&pb->mix.vDeltaAuxAR, &dsp_vptr->lastVolRa, dsp_vptr->volRa);
                            sal_setup_dspvol(&pb->mix.vDeltaAuxAS, &dsp_vptr->lastVolSa, dsp_vptr->volSa);
                            if ((pb->mix.vDeltaAuxAS | (pb->mix.vDeltaAuxAL | pb->mix.vDeltaAuxAR)) != 0)
                            {
                                pb->mixerCtrl |= 1;
                                needsDelta = 1;
                            }
                            else if ((pb->mix.vAuxAS | (pb->mix.vAuxAL | pb->mix.vAuxAR)) != 0)
                            {
                                pb->mixerCtrl |= 1;
                            }
                            else
                            {
                                pb->mixerCtrl &= ~1;
                            }
                        }
                        else if ((pb->mixerCtrl & 1) != 0)
                        {
                            u32 localNeedsDelta;
                            localNeedsDelta =
                                salCheckVolErrorAndResetDelta(&pb->mix.vAuxAL, &pb->mix.vDeltaAuxAL, &dsp_vptr->lastVolLa,
                                                              dsp_vptr->volLa, rampResetOffsetFlags, 8);
                            localNeedsDelta |=
                                salCheckVolErrorAndResetDelta(&pb->mix.vAuxAR, &pb->mix.vDeltaAuxAR, &dsp_vptr->lastVolRa,
                                                              dsp_vptr->volRa, rampResetOffsetFlags, 0x10);
                            localNeedsDelta |=
                                salCheckVolErrorAndResetDelta(&pb->mix.vAuxAS, &pb->mix.vDeltaAuxAS, &dsp_vptr->lastVolSa,
                                                              dsp_vptr->volSa, rampResetOffsetFlags, 0x20);
                            if ((localNeedsDelta | (pb->mix.vAuxAS | (pb->mix.vAuxAL | pb->mix.vAuxAR))) == 0)
                            {
                                pb->mixerCtrl &= ~1;
                            }
                            else
                            {
                                needsDelta = 1;
                            }
                        }
                        else
                        {
                            pb->mix.vDeltaAuxAL = 0;
                            pb->mix.vDeltaAuxAR = 0;
                            pb->mix.vDeltaAuxAS = 0;
                        }
                        if ((dsp_vptr->changed[0] & 4) != 0)
                        {
                            if (stp->type == SND_STUDIO_TYPE_STD)
                            {
                                sal_setup_dspvol(&pb->mix.vDeltaAuxBL, &dsp_vptr->lastVolLb, dsp_vptr->volLb);
                                sal_setup_dspvol(&pb->mix.vDeltaAuxBR, &dsp_vptr->lastVolRb, dsp_vptr->volRb);
                                sal_setup_dspvol(&pb->mix.vDeltaAuxBS, &dsp_vptr->lastVolSb, dsp_vptr->volSb);
                                if ((pb->mix.vDeltaAuxBS | (pb->mix.vDeltaAuxBL | pb->mix.vDeltaAuxBR)) != 0)
                                {
                                    pb->mixerCtrl |= 2;
                                    needsDelta = 1;
                                }
                                else if ((pb->mix.vAuxBS | (pb->mix.vAuxBL | pb->mix.vAuxBR)) != 0)
                                {
                                    pb->mixerCtrl |= 2;
                                }
                                else
                                {
                                    pb->mixerCtrl &= ~2;
                                }
                            }
                            else
                            {
                                sal_setup_dspvol(&pb->mix.vDeltaAuxBL, &dsp_vptr->lastVolLb, dsp_vptr->volLb);
                                sal_setup_dspvol(&pb->mix.vDeltaAuxBR, &dsp_vptr->lastVolRb, dsp_vptr->volRb);
                                if ((pb->mix.vDeltaAuxBL | pb->mix.vDeltaAuxBR) != 0)
                                {
                                    pb->mixerCtrl |= 0x10;
                                    needsDelta = 1;
                                }
                                else if ((pb->mix.vAuxBL | pb->mix.vAuxBR) != 0)
                                {
                                    pb->mixerCtrl |= 0x10;
                                }
                                else
                                {
                                    pb->mixerCtrl &= ~0x10;
                                }
                            }
                        }
                        else if (stp->type == SND_STUDIO_TYPE_STD)
                        {
                            if ((pb->mixerCtrl & 2) != 0)
                            {
                                u32 localNeedsDelta;
                                localNeedsDelta = salCheckVolErrorAndResetDelta(&pb->mix.vAuxBL, &pb->mix.vDeltaAuxBL,
                                                                                &dsp_vptr->lastVolLb, dsp_vptr->volLb,
                                                                                rampResetOffsetFlags, 0x40);
                                localNeedsDelta |= salCheckVolErrorAndResetDelta(&pb->mix.vAuxBR, &pb->mix.vDeltaAuxBR,
                                                                                 &dsp_vptr->lastVolRb, dsp_vptr->volRb,
                                                                                 rampResetOffsetFlags, 0x80);
                                localNeedsDelta |= salCheckVolErrorAndResetDelta(&pb->mix.vAuxBS, &pb->mix.vDeltaAuxBS,
                                                                                 &dsp_vptr->lastVolSb, dsp_vptr->volSb,
                                                                                 rampResetOffsetFlags, 0x100);
                                if ((localNeedsDelta | (pb->mix.vAuxBS | (pb->mix.vAuxBL | pb->mix.vAuxBR))) == 0)
                                {
                                    pb->mixerCtrl &= ~2;
                                }
                                else
                                {
                                    needsDelta = 1;
                                }
                            }
                            else
                            {
                                pb->mix.vDeltaAuxBL = 0;
                                pb->mix.vDeltaAuxBR = 0;
                                pb->mix.vDeltaAuxBS = 0;
                            }
                        }
                        else if ((pb->mixerCtrl & 0x10) != 0)
                        {
                            u32 localNeedsDelta;
                            localNeedsDelta =
                                salCheckVolErrorAndResetDelta(&pb->mix.vAuxBL, &pb->mix.vDeltaAuxBL, &dsp_vptr->lastVolLb,
                                                              dsp_vptr->volLb, rampResetOffsetFlags, 0x40);
                            localNeedsDelta |=
                                salCheckVolErrorAndResetDelta(&pb->mix.vAuxBR, &pb->mix.vDeltaAuxBR, &dsp_vptr->lastVolRb,
                                                              dsp_vptr->volRb, rampResetOffsetFlags, 0x80);
                            if ((localNeedsDelta | (pb->mix.vAuxBL | pb->mix.vAuxBR)) == 0)
                            {
                                if ((pb->mix.vAuxAS | pb->mix.vDeltaAuxAS) == 0)
                                {
                                    pb->mixerCtrl &= ~0x10;
                                }
                            }
                            else
                            {
                                needsDelta = 1;
                            }
                        }
                        else
                        {
                            pb->mix.vDeltaAuxBL = 0;
                            pb->mix.vDeltaAuxBR = 0;
                        }
                        if (needsDelta != 0)
                        {
                            pb->mixerCtrl |= 8;
                        }
                        else
                        {
                            pb->mixerCtrl &= ~8;
                        }
                        if (stp->type == SND_STUDIO_TYPE_STD)
                        {
                            if ((pb->mix.vS != 0) || (pb->mix.vDeltaS != 0) || (pb->mix.vAuxAS != 0) ||
                                (pb->mix.vDeltaAuxAS != 0) || (pb->mix.vAuxBS != 0) || (pb->mix.vDeltaAuxBS != 0))
                            {
                                pb->mixerCtrl |= 4;
                            }
                            else
                            {
                                pb->mixerCtrl &= ~4;
                            }
                        }
                        if ((dsp_vptr->changed[0] & DSP_VOICE_CHANGE_ITD) != 0)
                        {
                            pb->itd.targetShiftL = dsp_vptr->itdShiftL;
                            pb->itd.targetShiftR = dsp_vptr->itdShiftR;
                        }
                        if ((dsp_vptr->changed[0] & DSP_VOICE_CHANGE_SRC_TYPE) != 0)
                        {
                            pb->srcSelect = dsp_vptr->srcTypeSelect;
                        }
                        if ((dsp_vptr->changed[0] & DSP_VOICE_CHANGE_POLYPHASE) != 0)
                        {
                            pb->coefSelect = dsp_vptr->srcCoefSelect;
                        }
                        mix_start = 0;
                        newVoice = 0;
                        dsp_vptr->currentAddr = (pb->addr.currentAddressHi << 0x10) | pb->addr.currentAddressLo;
                    }
                    if ((dsp_vptr->changed[mix_start] & DSP_VOICE_CHANGE_KEYOFF) != 0)
                    {
                        adsrRelease(&dsp_vptr->adsr);
                    }
                    if ((dsp_vptr->changed[mix_start] & 8) != 0)
                    {
                        pb->src.ratioHi = dsp_vptr->pitch[mix_start] >> 0x10;
                        pb->src.ratioLo = dsp_vptr->pitch[mix_start];
                        dsp_vptr->playInfo.pitch = dsp_vptr->pitch[mix_start];
                    }
                    VoiceDone = adsrHandle(&dsp_vptr->adsr, &pb->ve.currentVolume, &pb->ve.currentDelta);
                    old_adsr_delta = pb->ve.currentDelta;
                    for (s = 0; s < 5; s++)
                    {
                        pb->update.updNum[s] = 0;
                    }
                    pptr = dsp_vptr->patchData;
                    pend = (u16*)((u32)dsp_vptr->patchData + 0x80);
                    if (mix_start != 0)
                    {
                        pptr[0] = 7;
                        pptr[1] = 1;
                        pptr += 2;
                        pb->update.updNum[mix_start]++;
                    }
                    sal_update_hostplayinfo(dsp_vptr);
                    for (s = mix_start + 1; s < 5; s++)
                    {
                        if (VoiceDone != 0)
                        {
                            pptr[0] = 7;
                            pptr[1] = 0;
                            pptr += 2;
                            pb->update.updNum[s]++;
                            salSynthSendMessage(dsp_vptr, 0);
                            salDeactivateVoice(dsp_vptr);
                            break;
                        }
                        else
                        {
                            if (rampResetOffsetFlags[s] != 0)
                            {
                                for (i = 0; i < 9; i++)
                                {
                                    if (((1 << i) & rampResetOffsetFlags[s]) != 0)
                                    {
                                        pptr[0] = pbOffsets[i];
                                        pptr[1] = 0;
                                        pptr += 2;
                                        pb->update.updNum[s]++;
                                    }
                                }
                            }
                            if ((dsp_vptr->changed[s] & DSP_VOICE_CHANGE_BREAK) != 0)
                            {
                                adsrStartRelease(&dsp_vptr->adsr, 10);
                                dsp_vptr->postBreak = 1;
                            }
                            else if (dsp_vptr->postBreak == 0)
                            {
                                if ((dsp_vptr->changed[s] & DSP_VOICE_CHANGE_KEYOFF) != 0)
                                {
                                    adsrRelease(&dsp_vptr->adsr);
                                }
                                if ((dsp_vptr->changed[s] & 8) != 0)
                                {
                                    pptr[0] = 0x53;
                                    pptr[1] = dsp_vptr->pitch[s] >> 16;
                                    pptr[2] = 0x54;
                                    pptr[3] = dsp_vptr->pitch[s];
                                    pptr += 4;
                                    pb->update.updNum[s] += 2;
                                    dsp_vptr->playInfo.pitch = dsp_vptr->pitch[s];
                                }
                            }
                            current_delta = dsp_vptr->adsr.currentDelta;
                            VoiceDone = adsrHandle(&dsp_vptr->adsr, &adsr_start, &adsr_delta);
                            if (old_adsr_delta == adsr_delta)
                            {
                                if (current_delta != 0)
                                {
                                    pptr[0] = 0x32;
                                    pptr[1] = adsr_start;
                                    pptr += 2;
                                    pb->update.updNum[s]++;
                                }
                            }
                            else
                            {
                                pptr[0] = 0x32;
                                pptr[1] = adsr_start;
                                pptr[2] = 0x33;
                                pptr[3] = adsr_delta;
                                pptr += 4;
                                pb->update.updNum[s] += 2;
                                old_adsr_delta = adsr_delta;
                            }
                            sal_update_hostplayinfo(dsp_vptr);
                        }
                    }
                    if (VoiceDone != 0)
                    {
                        salSynthSendMessage(dsp_vptr, 0);
                        salDeactivateVoice(dsp_vptr);
                    }
                    DCStoreRangeNoSync(dsp_vptr->patchData, (u32)pptr - (u32)dsp_vptr->patchData);
                    cyclesUsed += dspMixerCycles[pb->mixerCtrl] + 0x4FE;
                    switch (pb->src.ratioHi)
                    {
                    case 0:
                    case 1:
                        cyclesUsed += dspSRCCycles[pb->src.ratioHi][pb->srcSelect];
                        break;
                    default:
                        cyclesUsed += dspSRCCycles[2][pb->srcSelect];
                        break;
                    }
                    for (s = 0; s < 5; s++)
                    {
                        cyclesUsed += pb->update.updNum[s] * 4;
                    }
                    if (cyclesUsed > (OS_BUS_CLOCK / 400))
                    {
                        if ((newVoice == 0) && (VoiceDone == 0))
                        {
                            HandleDepopVoice(stp, dsp_vptr);
                        }
                        salDeactivateVoice(dsp_vptr);
                        salSynthSendMessage(dsp_vptr, 1);
                        for (voiceIdx = voiceIdx - 1; voiceIdx > 0; voiceIdx--)
                        {
                            if (voices[voiceIdx - 1]->state == DSP_VOICE_STATE_ACTIVE)
                            {
                                HandleDepopVoice(stp, voices[voiceIdx - 1]);
                            }
                            salDeactivateVoice(voices[voiceIdx - 1]);
                            salSynthSendMessage(voices[voiceIdx - 1], 1);
                        }
                        for (st1 = st + 1; st1 < salMaxStudioNum; st1++)
                        {
                            if (dspStudio[st1].state == DSP_STUDIO_STATE_ACTIVE)
                            {
                                for (dsp_vptr = dspStudio[st1].voiceRoot; dsp_vptr; dsp_vptr = next_dsp_vptr)
                                {
                                    next_dsp_vptr = dsp_vptr->next;
                                    if (dsp_vptr->state == DSP_VOICE_STATE_ACTIVE)
                                    {
                                        HandleDepopVoice(&dspStudio[st1], dsp_vptr);
                                    }
                                    salDeactivateVoice(dsp_vptr);
                                    salSynthSendMessage(dsp_vptr, 1);
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        if (!last_pb)
                        {
                            SAL_CHECK_CMD_SPACE(3);
                            dspCmdPtr[0] = 2;
                            dspCmdPtr[1] = (u32)pb >> 0x10;
                            dspCmdPtr[2] = (u32)pb;
                            dspCmdPtr += 3;
                            procVoiceFlag = 1;
                        }
                        else
                        {
                            last_pb->nextHi = (u32)pb >> 16;
                            last_pb->nextLo = (u32)pb;
                            procVoiceFlag = 1;
                            DCFlushRangeNoSync(last_pb, sizeof(_PB));
                        }
                        last_pb = pb;
                    }
                }
            }
            if (procVoiceFlag != 0)
            {
                SAL_CHECK_CMD_SPACE(1);
                *dspCmdPtr++ = 3;
            }
            if (last_pb)
            {
                last_pb->nextHi = 0;
                last_pb->nextLo = 0;
                DCFlushRangeNoSync(last_pb, sizeof(_PB));
            }
            getAuxFrame = (salAuxFrame + 1) % 3;
            if (stp->auxAHandler)
            {
                SAL_CHECK_CMD_SPACE(5);
                dspCmdPtr[0] = 4;
                dspCmdPtr[1] = (u32)stp->auxA[salAuxFrame] >> 16;
                dspCmdPtr[2] = (u32)stp->auxA[salAuxFrame];
                dspCmdPtr[3] = (u32)stp->auxA[getAuxFrame] >> 16;
                dspCmdPtr[4] = (u32)stp->auxA[getAuxFrame];
                dspCmdPtr += 5;
            }
            if (stp->type == SND_STUDIO_TYPE_STD)
            {
                if (stp->auxBHandler)
                {
                    SAL_CHECK_CMD_SPACE(5);
                    dspCmdPtr[0] = 5;
                    dspCmdPtr[1] = (u32)stp->auxB[salAuxFrame] >> 16;
                    dspCmdPtr[2] = (u32)stp->auxB[salAuxFrame];
                    dspCmdPtr[3] = (u32)stp->auxB[getAuxFrame] >> 16;
                    dspCmdPtr[4] = (u32)stp->auxB[getAuxFrame];
                    dspCmdPtr += 5;
                }
            }
            else
            {
                SAL_CHECK_CMD_SPACE(5);
                dspCmdPtr[0] = 16;
                dspCmdPtr[1] = (u32)stp->auxB[salFrame] >> 16;
                dspCmdPtr[2] = (u32)stp->auxB[salFrame];
                dspCmdPtr[3] = (u32)stp->auxB[salFrame ^ 1] >> 16;
                dspCmdPtr[4] = (u32)stp->auxB[salFrame ^ 1];
                dspCmdPtr += 5;
            }
            SAL_CHECK_CMD_SPACE(3);
            dspCmdPtr[0] = 6;
            dspCmdPtr[1] = (u32)stp->main[salFrame] >> 16;
            dspCmdPtr[2] = (u32)stp->main[salFrame];
            dspCmdPtr += 3;
            spb = stp->spb;
            DoDepopFade((s32*)&spb->dpopLHi, (s16*)&spb->dpopLDelta, &stp->hostDPopSum.l);
            DoDepopFade((s32*)&spb->dpopRHi, (s16*)&spb->dpopRDelta, &stp->hostDPopSum.r);
            DoDepopFade((s32*)&spb->dpopSHi, (s16*)&spb->dpopSDelta, &stp->hostDPopSum.s);
            DoDepopFade((s32*)&spb->dpopALHi, (s16*)&spb->dpopALDelta, &stp->hostDPopSum.lA);
            DoDepopFade((s32*)&spb->dpopARHi, (s16*)&spb->dpopARDelta, &stp->hostDPopSum.rA);
            DoDepopFade((s32*)&spb->dpopASHi, (s16*)&spb->dpopASDelta, &stp->hostDPopSum.sA);
            DoDepopFade((s32*)&spb->dpopBLHi, (s16*)&spb->dpopBLDelta, &stp->hostDPopSum.lB);
            DoDepopFade((s32*)&spb->dpopBRHi, (s16*)&spb->dpopBRDelta, &stp->hostDPopSum.rB);
            DoDepopFade((s32*)&spb->dpopBSHi, (s16*)&spb->dpopBSDelta, &stp->hostDPopSum.sB);
            DCFlushRangeNoSync(spb, sizeof(_SPB));
        }
    }
    SAL_CHECK_CMD_SPACE(3);
    dspCmdPtr[0] = 17;
    dspCmdPtr[1] = (u32)dspSurround >> 16;
    dspCmdPtr[2] = (u32)dspSurround;
    dspCmdPtr += 3;
    for (st = 0; st < salMaxStudioNum; st++)
    {
        if ((dspStudio[st].state == DSP_STUDIO_STATE_ACTIVE) && (dspStudio[st].isMaster != 0))
        {
            SAL_CHECK_CMD_SPACE(3);
            dspCmdPtr[0] = 9;
            dspCmdPtr[1] = (u32)dspStudio[st].main[salFrame] >> 16;
            dspCmdPtr[2] = (u32)dspStudio[st].main[salFrame];
            dspCmdPtr += 3;
        }
    }
    SAL_CHECK_CMD_SPACE(5);
    {
        u16 size;
        dspCmdPtr[0] = 14;
        dspCmdPtr[1] = (u32)dspSurround >> 16;
        dspCmdPtr[2] = (u32)dspSurround;
        dspCmdPtr[3] = (u32)dest >> 16;
        dspCmdPtr[4] = (u32)dest;
        dspCmdPtr += 5;
        *dspCmdPtr++ = 15;
        size = (((u32)dspCmdPtr - (u32)dspCmdCurBase) + 3) & 0xFFFC;
        if (dspCmdLastLoad)
        {
            dspCmdLastLoad[3] = size;
            DCStoreRangeNoSync(dspCmdLastBase, dspCmdLastSize);
        }
        else
        {
            dspCmdFirstSize = size;
        }
    }
    DCStoreRangeNoSync(dspCmdCurBase, (u32)dspCmdPtr - (u32)dspCmdCurBase);
}
