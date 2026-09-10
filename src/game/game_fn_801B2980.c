typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct PAGE {
    u16 macro;
    u8 prio;
    u8 maxVoices;
    u8 index;
    u8 reserved;
} PAGE;

typedef struct MIDI_CHANNEL_SETUP {
    u8 program;
    u8 volume;
    u8 panning;
    u8 reverb;
    u8 chorus;
} MIDI_CHANNEL_SETUP;

typedef struct MIDISETUP {
    u16 songId;
    u16 reserved;
    MIDI_CHANNEL_SETUP channel[16];
} MIDISETUP;

typedef struct ARR {
    u32 tTab;
    u32 pTab;
    u32 tmTab;
    u32 mTrack;
    u32 info;
    u32 loopPoint[16];
    u32 tsTab;
} ARR;

typedef struct SND_SEQVOLDEF {
    u8 track;
    u8 volGroup;
} SND_SEQVOLDEF;

typedef struct SND_PLAYPARA {
    u32 flags;
    u32 trackMute[2];
    u16 speed;
    struct {
        u16 time;
        u8 target;
    } volume;
    u8 numSeqVolDef;
    SND_SEQVOLDEF* seqVolDef;
    u8 numFaded;
    u8* faded;
} SND_PLAYPARA;

typedef struct TRACK {
    void* base;
    void* addr;
} TRACK;

typedef struct CPAT {
    u32 lTime;
    u32 baseTime;
    void* addr;
    void* patternInfo;
    u8 pitchBend[0xC];
    u8 modulation[0xC];
    u8 midi;
    u8 pad29[3];
} CPAT;

typedef struct NOTE NOTE;

typedef struct PRG_STATE {
    u16 macId;
    u8 priority;
    u8 maxVoices;
} PRG_STATE;

typedef struct MTRACK {
    void* base;
    void* addr;
} MTRACK;

typedef struct TICKS {
    u32 low;
    s32 high;
} TICKS;

typedef struct SEQ_SECTION {
    MTRACK mTrack;
    u32 bpm;
    TICKS tickDelta[2];
    void* globalEventRoot;
    TICKS time[2];
    u8 timeIndex;
    u8 pad31;
    u16 speed;
    u16 loopCnt;
    u8 loopDisable;
    u8 pad37;
} SEQ_SECTION;

typedef struct SEQ_INSTANCE SEQ_INSTANCE;
struct SEQ_INSTANCE {
    SEQ_INSTANCE* next;
    SEQ_INSTANCE* prev;
    u8 state;
    u8 index;
    u16 groupID;
    u32 publicId;
    PAGE* normtab;
    u8 normTrans[128];
    PAGE* drumtab;
    u8 drumTrans[128];
    ARR* arrbase;
    u32 trackMute[2];
    TRACK track[64];
    u8 trackVolGroup[64];
    CPAT pattern[64];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
    PRG_STATE prgState[16];
    u8 defVGroup;
    u8 padEB1[3];
    u8 syncCrossInfo[0x28];
    u32* syncSeqIdPtr;
    u8 syncActive;
    u8 defStudio;
    u8 keyOffCheck;
    u8 padEE3;
    u8 event[0x600];
    u8* trackSectionTab;
    SEQ_SECTION section[16];
};

extern SEQ_INSTANCE* lbl_8064D394;
extern SEQ_INSTANCE* lbl_8064D39C;
extern SEQ_INSTANCE* lbl_8064D380;
extern u32 lbl_8064D388;
extern u16 lbl_80619760[8][16];
extern u8 lbl_8061A434[64];
extern void fn_801B8164(u8, u16, u8, u8, u32);
extern void fn_801B85C8(u8, u8);
extern void fn_801B5B20(u32, u32, u8);
extern void fn_801CAEB8(u8, u32, u8);
extern void fn_801CB274(u8, u32);
extern void fn_801CA7C0(u8, u8, u32, u8);
extern void fn_801B3558(SEQ_INSTANCE*);
extern void fn_801B4E48(void);
extern u32 fn_801B2878(u32);

#define seqFreeRoot lbl_8064D394
#define seqActiveRoot lbl_8064D39C
#define cseq lbl_8064D380
#define curSeqId lbl_8064D388
#define seqMIDIPriority lbl_80619760
#define synthTrackVolume lbl_8061A434
#define synthVolume fn_801B8164
#define synthSetMusicVolumeType fn_801B85C8
#define synthSetBpm fn_801B5B20
#define inpResetMidiCtrl fn_801CAEB8
#define inpResetChannelDefaults fn_801CB274
#define inpSetMidiCtrl fn_801CA7C0
#define StartPause fn_801B3558
#define InitTrackEvents fn_801B4E48
#define GetPublicId fn_801B2878
#define ARR_GET(arr, offset) ((void*)((offset) + (u32)(arr)))

static inline void BuildTransTab(u8* tab, PAGE* page)
{
    u8 i;

    for (i = 0; i < 128; i++) {
        tab[i] = 0xff;
    }

    for (i = 0; page->index != 0xFF; i++, ++page) {
        tab[page->index] = i;
    }
}

static inline void DoPrgChange(SEQ_INSTANCE* seq, u8 prg, u8 midi)
{
    seqMIDIPriority[curSeqId][midi] = 0xFFFF;
    if (midi != 9) {
        prg = seq->normTrans[prg];
        if (prg == 0xFF) {
            return;
        }

        seq->prgState[midi].macId = seq->normtab[prg].macro;
        seq->prgState[midi].priority = seq->normtab[prg].prio;
        seq->prgState[midi].maxVoices = seq->normtab[prg].maxVoices;
        return;
    }

    prg = seq->drumTrans[prg];
    if (prg == 0xFF) {
        return;
    }

    seq->prgState[midi].macId = seq->drumtab[prg].macro;
    seq->prgState[midi].priority = seq->drumtab[prg].prio;
    seq->prgState[midi].maxVoices = seq->drumtab[prg].maxVoices;
}

u32 fn_801B2980(PAGE* norm, PAGE* drum, MIDISETUP* midiSetup, u32* song, SND_PLAYPARA* para,
                u8 studio, u16 sgid)
{
    ARR* arr;
    u32* tracktab;
    long i;
    SEQ_INSTANCE* nseq;
    SEQ_INSTANCE* oldCSeq;
    u32 seqId;
    u32 bpm;

    if ((nseq = seqFreeRoot) == 0) {
        return 0xffffffff;
    }
    if ((seqFreeRoot = nseq->next) != 0) {
        seqFreeRoot->prev = 0;
    }
    if ((nseq->next = seqActiveRoot) != 0) {
        seqActiveRoot->prev = nseq;
    }

    nseq->prev = 0;
    seqActiveRoot = nseq;
    nseq->state = 1;
    for (i = 0; i < 16; i++) {
        nseq->section[i].globalEventRoot = 0;
    }

    seqId = nseq->index;
    nseq->syncActive = 0;
    nseq->normtab = norm;
    nseq->drumtab = drum;
    nseq->arrbase = (ARR*)song;
    nseq->groupID = sgid;
    BuildTransTab(nseq->normTrans, nseq->normtab);
    BuildTransTab(nseq->drumTrans, nseq->drumtab);
    nseq->defVGroup = seqId + 23;
    for (i = 0; i < 64; i++) {
        nseq->trackVolGroup[i] = nseq->defVGroup;
    }

    nseq->defStudio = studio;
    if (para == 0) {
        nseq->trackMute[0] = -1;
        nseq->trackMute[1] = -1;
        for (i = 0; i < 16; i++) {
            nseq->section[i].speed = 256;
        }

        synthVolume(0x7f, 0, nseq->defVGroup, 0, 0xffffffff);
    } else {
        if (para->flags & 1) {
            nseq->trackMute[0] = para->trackMute[0];
            nseq->trackMute[1] = para->trackMute[1];
        } else {
            nseq->trackMute[0] = -1;
            nseq->trackMute[1] = -1;
        }

        if (para->flags & 2) {
            for (i = 0; i < 16; i++) {
                nseq->section[i].speed = para->speed;
            }
        } else {
            for (i = 0; i < 16; i++) {
                nseq->section[i].speed = 256;
            }
        }

        if (para->flags & 8) {
            for (i = 0; i < para->numSeqVolDef; i++) {
                nseq->trackVolGroup[para->seqVolDef[i].track] = para->seqVolDef[i].volGroup;
                synthSetMusicVolumeType(para->seqVolDef[i].volGroup, 0);
            }
        }

        if (para->flags & 4) {
            synthVolume(para->volume.target, para->volume.time, nseq->defVGroup, 0, 0xffffffff);

            for (i = 0; i < para->numFaded; i++) {
                synthVolume(para->volume.target, para->volume.time, para->faded[i], 0, 0xffffffff);
            }
        }
    }

    arr = (ARR*)song;
    if (arr->info & 0x80000000) {
        nseq->trackSectionTab = ARR_GET(arr, arr->tsTab);
    } else {
        nseq->trackSectionTab = 0;
    }

    bpm = arr->info & 0x0fffffff;

    if (!(arr->info & 0x40000000)) {
        bpm <<= 10;
    }

    for (i = 0; i < 16; i++) {
        nseq->section[i].bpm = bpm;
        synthSetBpm(bpm >> 10, seqId, i);

        if (arr->mTrack != 0) {
            nseq->section[i].mTrack.base = ARR_GET(arr, arr->mTrack);
            nseq->section[i].mTrack.addr = nseq->section[i].mTrack.base;
        } else {
            nseq->section[i].mTrack.base = 0;
        }

        nseq->section[i].loopDisable = 0;
        nseq->section[i].loopCnt = 0;
    }

    tracktab = ARR_GET(arr, arr->tTab);
    for (i = 0; i < 64; i++) {
        synthTrackVolume[i] = 0x7f;
        nseq->pattern[i].addr = 0;
        if (tracktab[i] != 0) {
            nseq->track[i].addr = nseq->track[i].base = ARR_GET(arr, tracktab[i]);
        } else {
            nseq->track[i].addr = nseq->track[i].base = 0;
        }
    }

    nseq->noteUsed[0] = 0;
    nseq->noteUsed[1] = 0;
    nseq->noteKeyOff = 0;

    for (i = 0; i < 16; i++) {
        inpResetMidiCtrl(i, seqId, 1);
    }
    for (i = 0; i < 16; i++) {
        nseq->prgState[i].macId = 0xffff;
    }
    for (i = 0; i < 16; i++) {
        inpResetChannelDefaults(i, seqId);
    }
    if (midiSetup != 0) {
        for (i = 0; i < 16; i++) {
            DoPrgChange(nseq, midiSetup->channel[i].program, i);
            inpSetMidiCtrl(7, i, seqId, midiSetup->channel[i].volume);
            inpSetMidiCtrl(10, i, seqId, midiSetup->channel[i].panning);
            inpSetMidiCtrl(0x5b, i, seqId, midiSetup->channel[i].reverb);
            inpSetMidiCtrl(0x5d, i, seqId, midiSetup->channel[i].chorus);
        }
    }
    for (i = 0; i < 16; i++) {
        seqMIDIPriority[seqId][i] = 0xffff;
    }
    for (i = 0; i < 16; i++) {
        nseq->section[i].time[0].high = 0;
        nseq->section[i].time[0].low = 0;
        nseq->section[i].time[1].high = 0;
        nseq->section[i].time[1].low = 0;
        nseq->section[i].timeIndex = 0;
    }
    nseq->keyOffCheck = 0;

    if (para != 0 && (para->flags & 0x10) != 0) {
        StartPause(nseq);
    }

    oldCSeq = cseq;
    cseq = nseq;
    InitTrackEvents();
    cseq = oldCSeq;
    seqId = GetPublicId(seqId);
    return seqId;
}
