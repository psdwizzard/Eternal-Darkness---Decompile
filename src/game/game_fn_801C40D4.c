typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct _PB {
    u8 pad00[4];
    u16 currHi;
    u16 currLo;
    u8 pad08[0x30];
    u16 itdBufferHi;
    u16 itdBufferLo;
    u8 pad3C[0x12];
    u16 updateDataHi;
    u16 updateDataLo;
    u8 pad52[0x6A];
} _PB;

typedef struct DSPvoice {
    _PB* pb;
    void* patchData;
    void* itdBuffer;
    u8 pad0C[0x18];
    u32 changed[5];
    u8 pad38[0xAC];
    u8 lastUpdatePitch;
    u8 lastUpdateVol;
    u8 lastUpdateVolA;
    u8 lastUpdateVolB;
    u32 virtualSampleID;
    u8 state;
    u8 postBreak;
    u8 startupBreak;
    u8 studio;
    u32 flags;
} DSPvoice;

typedef struct _DPOP {
    u32 l;
    u32 r;
    u32 s;
    u32 lA;
    u32 rA;
    u32 sA;
    u32 lB;
    u32 rB;
    u32 sB;
} _DPOP;

typedef struct DSPstudioinfo {
    void* spb;
    _DPOP hostDPopSum;
    s32* main[2];
    s32* auxA[3];
    s32* auxB[3];
    u8 pad48[8];
    u8 state;
    u8 pad51[0x6B];
} DSPstudioinfo;

extern u8 lbl_8064D4E5;
extern u8 lbl_8064D4E4;
extern u32 lbl_8064D478;
extern void* lbl_8064D498;
extern void* lbl_8064D4A4;
extern DSPvoice* lbl_8064D4AC;
extern void* lbl_8064D4A8;
extern void* lbl_8064D4A0;
extern DSPstudioinfo lbl_80628CB0[];

extern u32 fn_801CDA04(void);
extern void* fn_801CE330(u32);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void DCFlushRangeNoSync(void*, u32);
extern void DCInvalidateRange(void*, u32);
extern void fn_8020B7D8(void*, u32);
extern void fn_801C458C(u8, u32, u32);
extern void fn_801C4478(void);

#define salNumVoices lbl_8064D4E5
#define salMaxStudioNum lbl_8064D4E4
#define dspARAMZeroBuffer lbl_8064D478
#define dspCmdList lbl_8064D498
#define dspSurround lbl_8064D4A4
#define dspVoice lbl_8064D4AC
#define dspITDBuffer lbl_8064D4A8
#define dspCmdBuffer lbl_8064D4A0
#define dspStudio lbl_80628CB0

u32 fn_801C40D4(u8 numVoices, u8 numStudios, u32 defaultStudioDPL2)
{
    u32 i;
    u32 j;
    u32 itdPtr;

    salNumVoices = numVoices;
    salMaxStudioNum = numStudios;

    dspARAMZeroBuffer = fn_801CDA04();
    if ((dspCmdList = fn_801CE330(1024 * sizeof(u16)))) {
        if ((dspSurround = fn_801CE330(160 * sizeof(s32)))) {
            memset(dspSurround, 0, 160 * sizeof(s32));
            DCFlushRange(dspSurround, 160 * sizeof(s32));
            if ((dspVoice = fn_801CE330(salNumVoices * sizeof(DSPvoice)))) {
                if ((dspITDBuffer = fn_801CE330(salNumVoices * 64))) {
                    DCInvalidateRange(dspITDBuffer, salNumVoices * 64);
                    itdPtr = (u32)dspITDBuffer;
                    for (i = 0; i < salNumVoices; ++i) {
                        dspVoice[i].state = 0;
                        dspVoice[i].postBreak = 0;
                        dspVoice[i].startupBreak = 0;
                        dspVoice[i].lastUpdatePitch = 0xff;
                        dspVoice[i].lastUpdateVol = 0xff;
                        dspVoice[i].lastUpdateVolA = 0xff;
                        dspVoice[i].lastUpdateVolB = 0xff;
                        dspVoice[i].pb = fn_801CE330(sizeof(_PB));
                        memset(dspVoice[i].pb, 0, sizeof(_PB));
                        dspVoice[i].patchData = fn_801CE330(0x80);
                        dspVoice[i].pb->currHi = ((u32)dspVoice[i].pb >> 16);
                        dspVoice[i].pb->currLo = (u16)(u32)dspVoice[i].pb;
                        dspVoice[i].pb->updateDataHi = ((u32)dspVoice[i].patchData >> 16);
                        dspVoice[i].pb->updateDataLo = (u16)(u32)dspVoice[i].patchData;
                        dspVoice[i].pb->itdBufferHi = (itdPtr >> 16);
                        dspVoice[i].pb->itdBufferLo = itdPtr;
                        dspVoice[i].itdBuffer = (void*)itdPtr;
                        itdPtr += 0x40;
                        dspVoice[i].virtualSampleID = 0xFFFFFFFF;
                        fn_8020B7D8(dspVoice[i].pb, sizeof(_PB));
                        for (j = 0; j < 5; ++j) {
                            dspVoice[i].changed[j] = 0;
                        }
                    }

                    for (i = 0; i < salMaxStudioNum; ++i) {
                        dspStudio[i].state = 0;
                        if (!(dspStudio[i].spb = fn_801CE330(0x36))) {
                            return 0;
                        }
                        if (!(dspStudio[i].main[0] = fn_801CE330(0x3c00))) {
                            return 0;
                        }
                        memset(dspStudio[i].main[0], 0, 0x3c00);
                        DCFlushRangeNoSync(dspStudio[i].main[0], 0x3c00);
                        dspStudio[i].main[1] = dspStudio[i].main[0] + 0x1e0;
                        dspStudio[i].auxA[0] = dspStudio[i].main[1] + 0x1e0;
                        dspStudio[i].auxA[1] = dspStudio[i].auxA[0] + 0x1e0;
                        dspStudio[i].auxA[2] = dspStudio[i].auxA[1] + 0x1e0;
                        dspStudio[i].auxB[0] = dspStudio[i].auxA[2] + 0x1e0;
                        dspStudio[i].auxB[1] = dspStudio[i].auxB[0] + 0x1e0;
                        dspStudio[i].auxB[2] = dspStudio[i].auxB[1] + 0x1e0;
                        memset(dspStudio[i].spb, 0, 0x36);
                        dspStudio[i].hostDPopSum.l = dspStudio[i].hostDPopSum.r = dspStudio[i].hostDPopSum.s = 0;
                        dspStudio[i].hostDPopSum.lA = dspStudio[i].hostDPopSum.rA = dspStudio[i].hostDPopSum.sA = 0;
                        dspStudio[i].hostDPopSum.lB = dspStudio[i].hostDPopSum.rB = dspStudio[i].hostDPopSum.sB = 0;
                        DCFlushRangeNoSync(dspStudio[i].spb, 0x36);
                    }

                    fn_801C458C(0, 1, defaultStudioDPL2 != 0 ? 1 : 0);
                    if (!(dspCmdBuffer = fn_801CE330(0x100))) {
                        return 0;
                    }
                    fn_801C4478();
                    return 1;
                }
            }
        }
    }

    return 0;
}
