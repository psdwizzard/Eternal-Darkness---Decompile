typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef long long s64;

typedef struct ARR {
    u32 tTab;
    u32 pTab;
    u32 tmTab;
    u32 mTrack;
    u32 info;
    u32 loopPoint[16];
    u32 tsTab;
} ARR;

typedef struct MTRACK_DATA {
    u32 time;
    u32 bpm;
} MTRACK_DATA;

typedef struct MTRACK {
    MTRACK_DATA* base;
    MTRACK_DATA* addr;
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

typedef struct SEQ_INSTANCE SEQ_INSTANCE;
struct SEQ_INSTANCE {
    SEQ_INSTANCE* next;
    SEQ_INSTANCE* prev;
    u8 state;
    u8 index;
    u8 pad00A[0x118 - 0xA];
    ARR* arrbase;
    u8 pad11C[0xE64 - 0x11C];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
    u8 padE70[0xEB0 - 0xE70];
    u8 defVGroup;
    u8 padEB1[0xEE2 - 0xEB1];
    u8 keyOffCheck;
    u8 padEE3[0x14E4 - 0xEE3];
    u8* trackSectionTab;
    SEQ_SECTION section[16];
};

extern SEQ_INSTANCE* lbl_8064D380;
extern NOTE* lbl_8064D384;
extern u32 lbl_8064D388;
extern u8 lbl_8064D38C;
extern SEQ_INSTANCE* lbl_8064D394;
extern SEQ_INSTANCE* lbl_8064D39C;
extern u32 fn_801B8574(u8);
extern void fn_801B5B20(u32, u8, u8);
extern u32 fn_801B4FB4(u8, u32);
extern u32 fn_801B261C(void);
extern u32 fn_801B8F0C(u32);
extern void fn_801B2818(NOTE*);
extern void fn_801B244C(SEQ_INSTANCE*);
extern float fn_801023C0(float);

#define cseq lbl_8064D380
#define noteFree lbl_8064D384
#define curSeqId lbl_8064D388
#define curFadeOutState lbl_8064D38C
#define seqFreeRoot lbl_8064D394
#define seqActiveRoot lbl_8064D39C
#define synthIsFadeOutActive fn_801B8574
#define synthSetBpm fn_801B5B20
#define HandleTrackEvents fn_801B4FB4
#define HandleNotes fn_801B261C
#define sndFXCheck fn_801B8F0C
#define seqFreeKeyOffNote fn_801B2818
#define ResetNotes fn_801B244C
#define floorf fn_801023C0

static inline float fmodf(float x, float y)
{
    s64 n;

    if (__fabsf(y) > __fabsf(x)) {
        return x;
    }
    n = (s64)(x / y);
    return x - y * (float)n;
}

static inline void SetTickDelta(SEQ_SECTION* section, u32 deltaTime)
{
    float tickDelta = (float)section->bpm * (float)deltaTime * (1.f / (40960000.f));
    tickDelta *= section->speed * (1.f / 256.f);

    section->tickDelta[section->timeIndex].low = fmodf(tickDelta * 65536.f, 65536.f);
    section->tickDelta[section->timeIndex].high = floorf(tickDelta);
}

static inline void HandleMasterTrack(u8 secIndex)
{
    SEQ_SECTION* section;
    MTRACK_DATA* addr;
    u32 bpm;

    section = &cseq->section[secIndex];
    if (section->mTrack.base != 0) {
        while ((addr = section->mTrack.addr)->time != 0xFFFFFFFF) {
            if (addr->time > section->time[section->timeIndex].high) {
                break;
            }

            if (cseq->arrbase->info & 0x40000000) {
                bpm = addr->bpm;
                section->bpm = bpm;
                synthSetBpm(bpm >> 10, curSeqId, secIndex);
            } else {
                synthSetBpm(addr->bpm, curSeqId, secIndex);
                section->bpm = section->mTrack.addr->bpm << 10;
            }

            section->mTrack.addr++;
        }
    }
}

static inline void HandleKeyOffNotes(void)
{
    NOTE* n;
    NOTE* nn;
    if (!cseq->keyOffCheck) {
        n = cseq->noteKeyOff;
        while (n != 0) {
            nn = n->next;
            if (n->id != 0xffffffff && sndFXCheck(n->id) == 0xffffffff) {
                seqFreeKeyOffNote(n);
            }

            n = nn;
        }
    }

    cseq->keyOffCheck = (cseq->keyOffCheck + 1) % 5;
}

void fn_801B5228(u32 deltaTime)
{
    u32 x;
    u32 i;
    u32 j;
    u32 eventsActive;
    u32 notesActive;
    SEQ_INSTANCE* si;
    SEQ_INSTANCE* nextSi;

    if (deltaTime == 0) {
        return;
    }

    for (si = seqActiveRoot; si != 0; si = nextSi) {
        nextSi = si->next;
        cseq = si;
        curSeqId = si->index;
        curFadeOutState = synthIsFadeOutActive(si->defVGroup);

        if (cseq->trackSectionTab == 0) {
            HandleMasterTrack(0);
            SetTickDelta(cseq->section, deltaTime);
            eventsActive = HandleTrackEvents(0, deltaTime);
            notesActive = HandleNotes();
            HandleKeyOffNotes();

            for (i = 0; i < 2; i++) {
                x = cseq->section[0].time[i].low + cseq->section[0].tickDelta[i].low;
                cseq->section[0].time[i].low = x & 0xffff;
                x >>= 16;
                cseq->section[0].time[i].high += x + cseq->section[0].tickDelta[i].high;
            }
        } else {
            eventsActive = 0;
            for (i = 0; i < 16; i++) {
                HandleMasterTrack(i);
                SetTickDelta(&cseq->section[i], deltaTime);
                eventsActive |= HandleTrackEvents(i, deltaTime);
            }
            notesActive = HandleNotes();
            HandleKeyOffNotes();

            for (i = 0; i < 16; i++) {
                for (j = 0; j < 2; j++) {
                    x = cseq->section[i].time[j].low + cseq->section[i].tickDelta[j].low;
                    cseq->section[i].time[j].low = x & 0xffff;
                    x >>= 16;
                    cseq->section[i].time[j].high += x + cseq->section[i].tickDelta[j].high;
                }
            }
        }

        if (eventsActive == 0 && notesActive == 0) {
            if (si->prev != 0) {
                si->prev->next = nextSi;
            } else {
                seqActiveRoot = nextSi;
            }
            if (nextSi != 0) {
                nextSi->prev = si->prev;
            }
            ResetNotes(si);
            si->state = 0;
            si->prev = 0;
            if ((si->next = seqFreeRoot) != 0) {
                seqFreeRoot->prev = si;
            }
            seqFreeRoot = si;
        }
    }
}
