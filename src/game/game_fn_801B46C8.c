typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct PAGE {
    u16 macro;
    u8 prio;
    u8 maxVoices;
    u8 index;
    u8 reserved;
} PAGE;

typedef struct ARR {
    u32 tTab;
    u32 pTab;
    u32 tmTab;
    u32 mTrack;
    u32 info;
    u32 loopPoint[16];
    u32 tsTab;
} ARR;

typedef struct TENTRY {
    u32 time;
    u8 prgChange;
    u8 velocity;
    u8 res[2];
    u16 pattern;
    s8 transpose;
    s8 velocityAdd;
} TENTRY;

typedef struct SEQ_PATTERN {
    u32 headerLen;
    u32 pitchBend;
    u32 modulation;
    u32 noteData;
} SEQ_PATTERN;

typedef struct NOTE_DATA {
    u16 time;
    u8 key;
    u8 velocity;
    u16 length;
} NOTE_DATA;

typedef struct SEQ_STREAM {
    u8* nextAddr;
    u16 value;
    s16 nextDelta;
    u32 nextTime;
} SEQ_STREAM;

typedef struct CPAT {
    u32 lTime;
    u32 baseTime;
    NOTE_DATA* addr;
    TENTRY* patternInfo;
    SEQ_STREAM pitchBend;
    SEQ_STREAM modulation;
    u8 midi;
    u8 pad29[3];
} CPAT;

typedef struct NOTE NOTE;
struct NOTE {
    NOTE* next;
    NOTE* prev;
    u32 id;
    s32 endTime;
    u8 section;
    u8 timeIndex;
    u8 pad12[2];
};

typedef struct PRG_STATE {
    u16 macId;
    u8 priority;
    u8 maxVoices;
} PRG_STATE;

typedef struct SEQ_EVENT SEQ_EVENT;
struct SEQ_EVENT {
    SEQ_EVENT* next;
    SEQ_EVENT* prev;
    u32 time;
    union {
        TENTRY* trackAddr;
        struct {
            NOTE_DATA* addr;
            CPAT* base;
        } pattern;
    } info;
    u8 type;
    u8 trackId;
    u8 pad16[2];
};

typedef struct SND_CROSSFADE {
    u8 data[0x28];
} SND_CROSSFADE;

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
    u8 track[0x200];
    u8 trackVolGroup[64];
    CPAT pattern[64];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
    PRG_STATE prgState[16];
    u8 defVGroup;
    u8 padEB1[3];
    SND_CROSSFADE syncCrossInfo;
    u32* syncSeqIdPtr;
    u8 syncActive;
    u8 defStudio;
    u8 keyOffCheck;
    u8 padEE3;
    u8 event[0x600];
    u8* trackSectionTab;
    u8 section[0x380];
};

typedef struct SEQ_MEMORY {
    NOTE note[256];
    SEQ_INSTANCE instance[8];
    u16 midiPriority[8][16];
} SEQ_MEMORY;

typedef struct SYNTH_ITD_DEFAULT {
    u8 music;
    u8 sfx;
} SYNTH_ITD_DEFAULT;

static SEQ_MEMORY seqMem;

extern SEQ_INSTANCE* lbl_8064D380;
extern NOTE* lbl_8064D384;
extern u32 lbl_8064D388;
extern u8 lbl_8064D38C;
extern SYNTH_ITD_DEFAULT lbl_8061A4F4[8];
extern u8* fn_801B4398(u8*, u16*, s16*);
extern NOTE* fn_801B2528(u32, u8);
extern void fn_801B2748(void);
extern SEQ_EVENT* fn_801B443C(u8);
extern void fn_801CA7C0(u8, u8, u8, u8);
extern void fn_801CAD90(u8, u8, u8, u16);
extern void fn_801CAEB8(u8, u8, u8);
extern void fn_801B3E64(SND_CROSSFADE*, u32*, u8);
extern u32 fn_801B64D0(u16 id, u8 prio, u8 maxVoices, u8 key, u8 vol, u8 pan, u8 midi, u8 midiSet, u8 section,
                       u16 step, u16 trackid, u8 vGroup, s16 prioOffset, u8 studio, u32 itd);

#define cseq lbl_8064D380
#define noteFree lbl_8064D384
#define curSeqId lbl_8064D388
#define curFadeOutState lbl_8064D38C
#define synthITDDefault lbl_8061A4F4
#define seqMIDIPriority seqMem.midiPriority
#define GetStreamValue fn_801B4398
#define AllocateNote fn_801B2528
#define KeyOffNotes fn_801B2748
#define GenerateNextTrackEvent fn_801B443C
#define inpSetMidiCtrl fn_801CA7C0
#define inpSetMidiCtrl14 fn_801CAD90
#define inpResetMidiCtrl fn_801CAEB8
#define seqCrossFade fn_801B3E64
#define synthStartSound fn_801B64D0
#define ARR_GET(arr, offset) ((void*)((offset) + (u32)(arr)))
#define ARR_GET_TYPE(arr, offset, ty) ((ty)ARR_GET(arr, offset))
#define CLAMP(v, lo, hi) ((v) > (hi) ? (hi) : ((v) < (lo) ? (lo) : (v)))

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

static inline void InitStream(SEQ_STREAM* stream, u32 streamDataOffset)
{
    u16 delta;
    if (streamDataOffset != 0) {
        if ((stream->nextAddr = GetStreamValue(ARR_GET(cseq->arrbase, streamDataOffset), &delta,
                                               &stream->nextDelta)) != 0) {
            stream->nextTime = delta;
        } else {
            stream->nextTime = 0x7fffffff;
        }
    } else {
        stream->nextTime = 0x7fffffff;
    }
}

static inline u16 HandleStream(SEQ_STREAM* stream)
{
    u16 delta;
    stream->value += stream->nextDelta;
    if (stream->nextAddr != 0) {
        if ((stream->nextAddr = GetStreamValue(stream->nextAddr, &delta, &stream->nextDelta)) != 0) {
            stream->nextTime += delta;
        } else {
            stream->nextTime = 0x7fffffff;
        }
    } else {
        stream->nextTime = 0x7fffffff;
    }
    return stream->value;
}

static inline void FreeNote(NOTE* n)
{
    if (n->next != 0) {
        n->next->prev = n->prev;
    }

    if (n->prev != 0) {
        n->prev->next = n->next;
    } else {
        cseq->noteUsed[n->timeIndex] = n->next;
    }

    if ((n->next = noteFree) != 0) {
        noteFree->prev = n;
    }

    n->prev = 0;
    noteFree = n;
}

SEQ_EVENT* fn_801B46C8(SEQ_EVENT* event, u8 secIndex, u32* loopFlag)
{
    NOTE_DATA* pe;
    CPAT* pa;
    s32 key;
    s32 velocity;
    u8 midi;
    u16 macId;
    NOTE* note;
    TENTRY* tEntry;
    CPAT* pattern;
    u32* pTab;
    SEQ_PATTERN* pptr;

    switch (event->type) {
    case 4:
        tEntry = event->info.trackAddr;
        pattern = &cseq->pattern[event->trackId];
        pTab = ARR_GET(cseq->arrbase, cseq->arrbase->pTab);
        pptr = ARR_GET(cseq->arrbase, pTab[tEntry->pattern]);
        pattern->addr = (NOTE_DATA*)&pptr->noteData;
        pattern->lTime = 0;
        pattern->baseTime = tEntry->time;
        pattern->patternInfo = tEntry;
        InitStream(&pattern->pitchBend, pptr->pitchBend);
        pattern->pitchBend.value = 0x2000;
        InitStream(&pattern->modulation, pptr->modulation);
        pattern->modulation.value = 0;
        pattern->midi = ARR_GET_TYPE(cseq->arrbase, cseq->arrbase->tmTab, u8*)[event->trackId];
        if (tEntry->prgChange != 0xff) {
            DoPrgChange(cseq, tEntry->prgChange, pattern->midi);
        }
        if (tEntry->velocity != 0xff) {
            inpSetMidiCtrl(7, pattern->midi, curSeqId, tEntry->velocity);
        }
        break;

    case 0:
        pe = event->info.pattern.addr;
        pa = event->info.pattern.base;
        key = pe->key;
        velocity = pe->velocity;
        midi = pa->midi;

        if ((key & 0x80) != 0) {
            switch (velocity) {
            case 0:
                DoPrgChange(cseq, key & 0x7f, midi);
                break;
            case 1:
                inpSetMidiCtrl(0x82, midi, curSeqId, key & 0x7f);
                break;
            default:
                if ((velocity & 0x80) != 0x80) {
                    break;
                }
                switch (velocity & 0x7f) {
                case 0x68:
                    if (cseq->syncActive) {
                        seqCrossFade(&cseq->syncCrossInfo, cseq->syncSeqIdPtr, 1);
                        cseq->syncActive = 0;
                    }
                    break;
                case 0x69:
                    seqMIDIPriority[curSeqId][midi] = key & 0x7f;
                    break;
                case 0x6a:
                    seqMIDIPriority[curSeqId][midi] = (key & 0x7f) + 0x80;
                    break;
                case 0x79:
                    inpResetMidiCtrl(midi, curSeqId, 0);
                    break;
                case 0x7b:
                    KeyOffNotes();
                    break;
                default:
                    inpSetMidiCtrl(velocity & 0x7f, midi, curSeqId, key & 0x7f);
                    break;
                }
            }
            break;
        }

        if ((cseq->trackMute[event->trackId / 32] & (1 << (event->trackId & 0x1f))) != 0) {
            if ((macId = cseq->prgState[midi].macId) != 0xffff) {
                key += pa->patternInfo->transpose;
                key = CLAMP(key, 0, 0x7f);

                velocity += pa->patternInfo->velocityAdd;
                velocity = CLAMP(velocity, 0, 0x7f);

                if ((note = AllocateNote(event->time + pe->length, secIndex)) != 0) {
                    if ((note->id = synthStartSound(
                             macId, cseq->prgState[midi].priority, cseq->prgState[midi].maxVoices,
                             key, velocity, 64, midi, curSeqId, secIndex, 0, event->trackId,
                             cseq->trackVolGroup[event->trackId], curFadeOutState ? -1 : 0, cseq->defStudio,
                             synthITDDefault[cseq->defStudio].music)) == 0xffffffff) {
                        FreeNote(note);
                    }
                }
            }
        }
        break;

    case 2:
        pa = event->info.pattern.base;
        inpSetMidiCtrl14(0x80, pa->midi, curSeqId, HandleStream(&pa->pitchBend));
        break;

    case 1:
        pa = event->info.pattern.base;
        inpSetMidiCtrl14(1, pa->midi, curSeqId, HandleStream(&pa->modulation));
        break;

    case 3:
        *loopFlag |= 1;
        return 0;
    }

    return GenerateNextTrackEvent(event->trackId);
}
