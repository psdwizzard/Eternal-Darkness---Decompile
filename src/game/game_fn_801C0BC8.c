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

extern SYNTH_VOICE* synthVoice;
extern SYNTH_VOICE* macActiveMacroRoot;
extern u8* dataGetMacro(u16);
extern u16 seqGetMIDIPriority(u8, u8);
extern u32 voiceAllocate(u8, u8, u16, u8);
extern void vidRemoveVoiceReferences(SYNTH_VOICE*);
extern void UnYieldMacro(SYNTH_VOICE*, u32);
extern u32 hwIsActive(u32);
extern void inpResetMidiCtrl(u8, u8, u8);
extern void inpResetChannelDefaults(u8, u8);
extern void voiceSetPriority(SYNTH_VOICE*, u8);
extern u32 vidMakeNew(SYNTH_VOICE*, u32);
extern void hwBreak(u32);
extern void voiceFree(SYNTH_VOICE*);

#define macActiveRoot macActiveMacroRoot

u32 macStart(u16 macid, u8 priority, u8 maxVoices, u16 allocId, u8 key, u8 vol, u8 panning, u8 midi, u8 midiSet,
                u8 section, u16 step, u16 trackid, u8 new_vid, u8 vGroup, u8 studio, u32 itd)
{
    u32 voice;
    u32 vid;
    s32 fxFlag;
    u8* addr;
    SYNTH_VOICE* sv;
    u16 seqPrio;

    if ((addr = dataGetMacro(macid)) != 0) {
        fxFlag = key & 0x80;
        if (!fxFlag && (seqPrio = seqGetMIDIPriority(midiSet, midi)) != 0xffff) {
            priority = seqPrio;
        }

        if ((voice = voiceAllocate(priority, maxVoices, allocId, fxFlag != 0 ? 1 : 0)) != 0xffffffff) {
            sv = &synthVoice[voice];
            vidRemoveVoiceReferences(sv);
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
                UnYieldMacro(sv, 1);
                sv->macState = 2;
            }
            *(u64*)&sv->cFlagsHi = (*(u64*)&sv->cFlagsHi & 0x10) | 2;

            if (hwIsActive(voice)) {
                sv->cFlagsLo |= 1;
            }

            *(u64*)&sv->waitHi = 0;

            if (fxFlag != 0) {
                sv->fxFlag = 1;
                key &= 0x7f;
                inpResetMidiCtrl((u8)voice, 0xff, 1);
                inpResetChannelDefaults((u8)voice, 0xff);
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
            voiceSetPriority(sv, priority);

            if ((vid = vidMakeNew(sv, new_vid)) != 0xffffffff) {
                if (sv->macState != 0) {
                    UnYieldMacro(sv, 0);
                    if ((sv->nextMacActive = macActiveRoot) != 0) {
                        macActiveRoot->prevMacActive = sv;
                    }
                    sv->prevMacActive = 0;
                    macActiveRoot = sv;
                    sv->macState = 0;
                }
                return vid;
            }

            if (hwIsActive(voice)) {
                hwBreak(voice);
            }
            voiceFree(sv);
        }
    }

    return 0xffffffff;
}
