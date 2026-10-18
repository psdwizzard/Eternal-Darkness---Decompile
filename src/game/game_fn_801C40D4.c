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

extern u8 salNumVoices;
extern u8 salMaxStudioNum;
extern u32 dspARAMZeroBuffer;
extern void* dspCmdList;
extern void* dspSurround;
extern DSPvoice* dspVoice;
extern void* dspITDBuffer;
extern void* dspHrtfHistoryBuffer;
extern DSPstudioinfo lbl_80628CB0[];

extern u32 aramGetZeroBuffer(void);
extern void* salMalloc(u32);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void DCFlushRangeNoSync(void*, u32);
extern void DCInvalidateRange(void*, u32);
extern void DCStoreRangeNoSync(void*, u32);
extern void salActivateStudio(u8, u32, u32);
extern void salInitHRTFBuffer(void);

#define dspCmdBuffer dspHrtfHistoryBuffer
#define dspStudio lbl_80628CB0

u32 salInitDspCtrl(u8 numVoices, u8 numStudios, u32 defaultStudioDPL2)
{
    u32 i;
    u32 j;
    u32 itdPtr;

    salNumVoices = numVoices;
    salMaxStudioNum = numStudios;

    dspARAMZeroBuffer = aramGetZeroBuffer();
    if ((dspCmdList = salMalloc(1024 * sizeof(u16)))) {
        if ((dspSurround = salMalloc(160 * sizeof(s32)))) {
            memset(dspSurround, 0, 160 * sizeof(s32));
            DCFlushRange(dspSurround, 160 * sizeof(s32));
            if ((dspVoice = salMalloc(salNumVoices * sizeof(DSPvoice)))) {
                if ((dspITDBuffer = salMalloc(salNumVoices * 64))) {
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
                        dspVoice[i].pb = salMalloc(sizeof(_PB));
                        memset(dspVoice[i].pb, 0, sizeof(_PB));
                        dspVoice[i].patchData = salMalloc(0x80);
                        dspVoice[i].pb->currHi = ((u32)dspVoice[i].pb >> 16);
                        dspVoice[i].pb->currLo = (u16)(u32)dspVoice[i].pb;
                        dspVoice[i].pb->updateDataHi = ((u32)dspVoice[i].patchData >> 16);
                        dspVoice[i].pb->updateDataLo = (u16)(u32)dspVoice[i].patchData;
                        dspVoice[i].pb->itdBufferHi = (itdPtr >> 16);
                        dspVoice[i].pb->itdBufferLo = itdPtr;
                        dspVoice[i].itdBuffer = (void*)itdPtr;
                        itdPtr += 0x40;
                        dspVoice[i].virtualSampleID = 0xFFFFFFFF;
                        DCStoreRangeNoSync(dspVoice[i].pb, sizeof(_PB));
                        for (j = 0; j < 5; ++j) {
                            dspVoice[i].changed[j] = 0;
                        }
                    }

                    for (i = 0; i < salMaxStudioNum; ++i) {
                        dspStudio[i].state = 0;
                        if (!(dspStudio[i].spb = salMalloc(0x36))) {
                            return 0;
                        }
                        if (!(dspStudio[i].main[0] = salMalloc(0x3c00))) {
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

                    salActivateStudio(0, 1, defaultStudioDPL2 != 0 ? 1 : 0);
                    if (!(dspCmdBuffer = salMalloc(0x100))) {
                        return 0;
                    }
                    salInitHRTFBuffer();
                    return 1;
                }
            }
        }
    }

    return 0;
}
