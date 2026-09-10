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

typedef struct MTRACK {
    void* base;
    void* addr;
} MTRACK;

typedef struct TICKS {
    u32 low;
    s32 high;
} TICKS;

typedef struct SEQ_EVENT SEQ_EVENT;
struct SEQ_EVENT {
    SEQ_EVENT* next;
    SEQ_EVENT* prev;
    u32 time;
    u8 pad0C[0xC];
};

typedef struct SEQ_SECTION {
    MTRACK mTrack;
    u32 bpm;
    TICKS tickDelta[2];
    SEQ_EVENT* globalEventRoot;
    TICKS time[2];
    u8 timeIndex;
    u8 pad31;
    u16 speed;
    u16 loopCnt;
    u8 loopDisable;
    u8 pad37;
} SEQ_SECTION;

typedef struct SEQ_INSTANCE {
    u8 pad000[0x118];
    ARR* arrbase;
    u8 pad11C[0x14E8 - 0x11C];
    SEQ_SECTION section[16];
} SEQ_INSTANCE;

extern SEQ_INSTANCE* lbl_8064D380;
extern void fn_801B3470(u8);
extern void fn_801B4EF0(u8);
extern SEQ_EVENT* fn_801B46C8(SEQ_EVENT*, u8, u32*);
extern void fn_801B4654(SEQ_SECTION*, SEQ_EVENT*);
extern float fn_801023C0(float);

#define cseq lbl_8064D380
#define HandleMasterTrack fn_801B3470
#define InitTrackEventsSection fn_801B4EF0
#define HandleEvent fn_801B46C8
#define InsertGlobalEvent fn_801B4654
#define floorf fn_801023C0

static inline float fmodf(float x, float y)
{
    if (__fabsf(y) > __fabsf(x)) {
        return x;
    }
    return x - y * (float)(s64)(x / y);
}

static inline u32 GetNextEventTime(SEQ_SECTION* section)
{
    return section->globalEventRoot == 0 ? 0 : section->globalEventRoot->time;
}

static inline SEQ_EVENT* GetGlobalEvent(SEQ_SECTION* section)
{
    SEQ_EVENT* ev;
    ev = section->globalEventRoot;
    if (ev != 0 && ((section->globalEventRoot = ev->next) != 0)) {
        section->globalEventRoot->prev = 0;
    }
    return ev;
}

static inline void SetTickDelta(SEQ_SECTION* section, u32 deltaTime)
{
    float tickDelta = (float)section->bpm * (float)deltaTime * (1.f / (40960000.f));
    tickDelta *= section->speed * (1.f / 256.f);

    section->tickDelta[section->timeIndex].low = fmodf(tickDelta * 65536.f, 65536.f);
    section->tickDelta[section->timeIndex].high = floorf(tickDelta);
}

static inline void RewindMTrack(u8 secIndex, u32 deltaTime)
{
    if (cseq->section[secIndex].mTrack.base == 0) {
        return;
    }
    cseq->section[secIndex].mTrack.addr = cseq->section[secIndex].mTrack.base;
    HandleMasterTrack(secIndex);
    SetTickDelta(cseq->section + secIndex, deltaTime);
}

u32 fn_801B4FB4(u8 secIndex, u32 deltaTime)
{
    SEQ_EVENT* ev;
    u32 loopFlag;
    SEQ_SECTION* section;

    section = &cseq->section[secIndex];
    loopFlag = 0;

    while (GetNextEventTime(section) <= section->time[section->timeIndex].high) {
        if ((ev = GetGlobalEvent(section)) == 0) {
            if (!loopFlag) {
                return 0;
            }

            loopFlag = 0;
            section->timeIndex ^= 1;
            section->time[section->timeIndex].high = cseq->arrbase->loopPoint[secIndex];
            section->time[section->timeIndex].low = section->time[section->timeIndex ^ 1].low;
            RewindMTrack(secIndex, deltaTime);
            section->loopCnt += 1;
            InitTrackEventsSection(secIndex);
            continue;
        }

        if ((ev = HandleEvent(ev, secIndex, &loopFlag)) != 0) {
            InsertGlobalEvent(section, ev);
        }
    }

    return 1;
}
