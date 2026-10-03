typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct MSTEP {
    u32 para[2];
} MSTEP;

typedef struct VID_LIST {
    u8 pad_00[8];
    u32 vid;
} VID_LIST;

typedef struct SYNTH_VOICE {
    u8 pad_000[0x34];
    MSTEP* addr;
    MSTEP* curAddr;
    u8 pad_03C[0x14];
    MSTEP* trapEventAddr[3];
    MSTEP* trapEventCurAddr[3];
    u8 trapEventAny;
    u8 pad_069[0x43];
    s32 local_vars[16];
    u8 pad_0EC[0xC];
    VID_LIST* vidList;
    u8 pad_0FC[6];
    u16 macroId;
    u8 pad_104[0x2E8];
    u8 mesgNum;
    u8 mesgRead;
    u8 mesgWrite;
    u8 pad_3EF;
    s32 mesgQueue[4];
    u8 pad_400[4];
} SYNTH_VOICE;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceNum;
} SynthInfo;

extern SynthInfo lbl_80619C20;
extern s32 lbl_8061A504[];
extern SYNTH_VOICE* lbl_8064D3D0;
extern void (*lbl_8064D3D4)(u32, s32);
extern u32 fn_801C14D0(u32);
extern void fn_801C09C4(SYNTH_VOICE*);

#define synthVoice lbl_8064D3D0
#define synthGlobalVariable lbl_8061A504
#define synthMessageCallback lbl_8064D3D4

static inline s32 varGet32(SYNTH_VOICE* svoice, u8 index)
{
    s32 value;

    index &= 0x1F;
    if (index < 16) {
        value = svoice->local_vars[index];
    } else {
        value = synthGlobalVariable[index - 16];
    }
    return value;
}

static inline u32 ExecuteTrap(SYNTH_VOICE* svoice, u8 trapType)
{
    if (svoice->trapEventAny != 0 && svoice->trapEventAddr[trapType] != 0) {
        svoice->curAddr = svoice->trapEventCurAddr[trapType];
        svoice->addr = svoice->trapEventAddr[trapType];
        svoice->trapEventAddr[trapType] = 0;
        fn_801C09C4(svoice);
        return 1;
    }

    return 0;
}

static inline u32 macPostMessage(u32 vid, s32 mesg)
{
    SYNTH_VOICE* sv;

    if ((vid = fn_801C14D0(vid)) != (u32)-1 && (sv = &synthVoice[vid & 0xFF])->mesgNum < 4) {
        ++sv->mesgNum;
        sv->mesgQueue[sv->mesgWrite] = mesg;
        sv->mesgWrite = (sv->mesgWrite + 1) & 3;
        ExecuteTrap(sv, 2);
        return 1;
    }

    return 0;
}

void fn_801BEC38(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    u8 i;
    s32 mesg;
    u16 macro;

    mesg = varGet32(svoice, (u8)(cstep->para[1] >> 8));

    if (!(u8)(cstep->para[0] >> 8)) {
        macro = (u16)(cstep->para[0] >> 16);
        if (macro != 0xFFFF) {
            for (i = 0; i < lbl_80619C20.voiceNum; ++i) {
                if (synthVoice[i].addr != 0 && macro == synthVoice[i].macroId) {
                    macPostMessage(synthVoice[i].vidList->vid, mesg);
                }
            }
        } else if (synthMessageCallback != 0) {
            synthMessageCallback(svoice->vidList->vid, mesg);
        }
    } else {
        macPostMessage(varGet32(svoice, (u8)cstep->para[1]), mesg);
    }
}
