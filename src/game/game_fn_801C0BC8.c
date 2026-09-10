typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0x34];
    u8* addr;
    u8* curAddr;
    struct SYNTH_VOICE* nextMacActive;
    struct SYNTH_VOICE* prevMacActive;
    u8 pad_044[8];
    s32 macState;
    u8 pad_050[0x3C];
    u8 callStackEntryNum;
    u8 callStackIndex;
    u8 pad_08E[0xA];
    u32 waitHi;
    u32 waitLo;
    u8 pad_0A0[0x4C];
    u32 child;
    u32 parent;
    u32 id;
    u8 pad_0F8[8];
    u16 allocId;
    u16 macroId;
    u8 pad_104[4];
    u32 lastVID;
    u8 pad_10C[2];
    u16 ageSpeed;
    u32 age;
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 pad_11C;
    u8 fxFlag;
    u8 pad_11E[0xE];
    u16 curNote;
    s8 curDetune;
    u8 orgNote;
    u8 pad_130[0xD8];
    u8 vol;
    u8 pan;
    u8 midi;
    u8 midiSet;
    u8 section;
    u8 track;
    u8 vGroup;
    u8 studio;
    u8 itdMode;
    u8 pad_211[0x1DB];
    u8 mesgNum;
    u8 mesgRead;
    u8 mesgWrite;
    u8 pad_3EF[0x15];
} SYNTH_VOICE;
#pragma pack()

extern SYNTH_VOICE* lbl_8064D3D0;
extern SYNTH_VOICE* lbl_8064D43C;
extern u8* fn_801BCEB0(u16);
extern u16 fn_801B8D68(u8, u8);
extern u32 fn_801C1790(u8, u8, u16, u8);
extern void fn_801C106C(SYNTH_VOICE*);
extern void fn_801C08E8(SYNTH_VOICE*, u32);
extern u32 fn_801CC6DC(u32);
extern void fn_801CAEB8(u8, u8, u8);
extern void fn_801CB274(u8, u8);
extern void fn_801C1600(SYNTH_VOICE*, u8);
extern u32 fn_801C13D4(SYNTH_VOICE*, u32);
extern void fn_801CC8C4(u32);
extern void fn_801C1BCC(SYNTH_VOICE*);

#define synthVoice lbl_8064D3D0
#define macActiveRoot lbl_8064D43C

u32 fn_801C0BC8(u16 macid, u8 priority, u8 maxVoices, u16 allocId, u8 key, u8 vol, u8 panning, u8 midi, u8 midiSet,
                u8 section, u16 step, u16 trackid, u8 new_vid, u8 vGroup, u8 studio, u32 itd)
{
    u32 voice;
    u32 vid;
    s32 fxFlag;
    u8* addr;
    SYNTH_VOICE* sv;
    u16 seqPrio;

    if ((addr = fn_801BCEB0(macid)) != 0) {
        fxFlag = key & 0x80;
        if (!fxFlag && (seqPrio = fn_801B8D68(midiSet, midi)) != 0xffff) {
            priority = seqPrio;
        }

        if ((voice = fn_801C1790(priority, maxVoices, allocId, fxFlag != 0 ? 1 : 0)) != 0xffffffff) {
            sv = &synthVoice[voice];
            fn_801C106C(sv);
            if (sv->macState != 2) {
                if (sv->macState == 0) {
                    if (sv->prevMacActive == 0) {
                        macActiveRoot = sv->nextMacActive;
                    } else {
                        sv->prevMacActive->nextMacActive = sv->nextMacActive;
                    }
                    if (sv->nextMacActive != 0) {
                        sv->nextMacActive->prevMacActive = sv->prevMacActive;
                    }
                }
                fn_801C08E8(sv, 1);
                sv->macState = 2;
            }
            *(u64*)&sv->cFlagsHi = (*(u64*)&sv->cFlagsHi & 0x10) | 2;

            if (fn_801CC6DC(voice)) {
                sv->cFlagsLo |= 1;
            }

            *(u64*)&sv->waitHi = 0;

            if (fxFlag != 0) {
                sv->fxFlag = 1;
                key &= 0x7f;
                fn_801CAEB8((u8)voice, 0xff, 1);
                fn_801CB274((u8)voice, 0xff);
                sv->midi = voice;
                sv->midiSet = 0xff;
                sv->section = 0;
            } else {
                sv->fxFlag = 0;
                sv->midi = midi;
                sv->midiSet = midiSet;
                sv->section = section;
            }

            sv->macroId = macid;
            sv->allocId = allocId;
            sv->age = 0x75300000;
            sv->ageSpeed = 0x400;
            sv->addr = addr;
            sv->curAddr = addr + (step << 3);
            sv->orgNote = key;
            sv->curNote = key;
            sv->curDetune = 0;
            sv->vol = vol;
            sv->pan = panning;
            sv->track = trackid;
            sv->callStackEntryNum = 0;
            sv->callStackIndex = 0;
            sv->child = 0xffffffff;
            sv->parent = 0xffffffff;
            sv->lastVID = 0xffffffff;
            sv->vGroup = vGroup;
            sv->studio = studio;
            sv->itdMode = itd != 0 ? 0 : 1;
            sv->mesgWrite = 0;
            sv->mesgRead = 0;
            sv->mesgNum = 0;
            sv->id = voice | ((macid << 0x10) | ((key & 0xff) << 8));
            fn_801C1600(sv, priority);

            if ((vid = fn_801C13D4(sv, new_vid)) != 0xffffffff) {
                if (sv->macState != 0) {
                    fn_801C08E8(sv, 0);
                    if ((sv->nextMacActive = macActiveRoot) != 0) {
                        macActiveRoot->prevMacActive = sv;
                    }
                    sv->prevMacActive = 0;
                    macActiveRoot = sv;
                    sv->macState = 0;
                }
                return vid;
            }

            if (fn_801CC6DC(voice)) {
                fn_801CC8C4(voice);
            }
            fn_801C1BCC(sv);
        }
    }

    return 0xffffffff;
}
