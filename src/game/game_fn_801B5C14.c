typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct McmdVoiceState {
    u8 pad000[0xEC];
    u32 child;
    u32 parent;
    u32 id;
    u8 padF8[0x114 - 0xF8];
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 block;
    u8 pad11D[4];
    u8 midi;
    u8 midiSet;
    u8 pad123[9];
    u16 curNote;
    s8 curDetune;
    u8 orgNote;
    u8 lastNote;
    u8 pad131[7];
    u32 portCurPitch;
    u32 portTime;
    u8 pad140[0x404 - 0x140];
} McmdVoiceState;

typedef struct SynthInfo {
    u8 pad[0x210];
    u8 voiceCount;
} SynthInfo;

extern SynthInfo lbl_80619C20;
extern McmdVoiceState* lbl_8064D3D0;
extern u32 fn_801CC6DC(u32);
extern void fn_801C106C(McmdVoiceState*);
extern u32 fn_801C13D4(McmdVoiceState*, u32);
extern void fn_801C26F8(McmdVoiceState*);
extern void fn_801CB470(u8, u8, u8);

#define SYNTH_CONFIGURATION (&lbl_80619C20)
#define synthVoice lbl_8064D3D0
#define hwIsActive fn_801CC6DC
#define vidRemoveVoiceReferences fn_801C106C
#define vidMakeNew fn_801C13D4
#define voiceSetLastStarted fn_801C26F8
#define inpSetMidiLastNote fn_801CB470

u32 fn_801B5C14(u8 key, u8 midi, u8 midiSet, u32 isMaster, u32* rejected)
{
    u32 i;
    u32 result;
    u32 previousId;
    McmdVoiceState* voice;
    McmdVoiceState* selectedVoice;
    u32 sawHeldVoice;

    sawHeldVoice = 0;
    result = -1;
    for (i = 0, voice = (McmdVoiceState*)synthVoice; i < SYNTH_CONFIGURATION->voiceCount; ++i, ++voice) {
        if (voice->block == 0 && voice->id != 0xffffffff && voice->midi == midi && voice->midiSet == midiSet) {
            if ((*(u64*)&voice->cFlagsHi & 2) != 0) {
                sawHeldVoice = 1;
            }
            if ((*(u64*)&voice->cFlagsHi & 0x10) != 0 && (*(u64*)&voice->cFlagsHi & 0x10000000008) != 8 && hwIsActive(i) != 0) {
                if (result == 0xffffffff && (*(u64*)&voice->cFlagsHi & 0x20002) == 0x20002) {
                    *rejected = 1;
                    return -1;
                }

                selectedVoice = voice;
                voice->portCurPitch = ((u32)voice->curNote << 16) + ((s32)voice->curDetune << 16) / 100;
                voice->lastNote = voice->curNote;
                voice->curNote = key + ((voice->curNote & 0xff) - voice->orgNote);
                voice->orgNote = key;
                voice->curDetune = 0;
                voice->portTime = 0;
                voice->cFlagsLo = voice->cFlagsLo | 0x20000LL;
                vidRemoveVoiceReferences(&synthVoice[i]);
                if (result == 0xffffffff) {
                    voice->child = 0xffffffff;
                    voice->parent = 0xffffffff;
                    result = vidMakeNew(&synthVoice[i], isMaster);
                    previousId = voice->id;
                } else {
                    ((McmdVoiceState*)synthVoice)[previousId & 0xff].child = voice->id;
                    voice->parent = previousId;
                    previousId = voice->id;
                    vidMakeNew(&synthVoice[i], 0);
                }
            }
        }
    }

    if (result != 0xffffffff) {
        voiceSetLastStarted(selectedVoice);
        inpSetMidiLastNote(selectedVoice->midi, selectedVoice->midiSet, selectedVoice->curNote & 0xff);
        *rejected = 0;
    } else {
        *rejected = sawHeldVoice;
    }
    return result;
}
