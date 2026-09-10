typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct NOTE NOTE;
struct NOTE {
    NOTE* next;
    NOTE* prev;
    u32 id;
    s32 endTime;
    u8 section;
    u8 pad11[3];
};

typedef struct SEQ_INSTANCE SEQ_INSTANCE;
struct SEQ_INSTANCE {
    SEQ_INSTANCE* next;
    SEQ_INSTANCE* prev;
    u8 state;
    u8 index;
    u8 pad0A[2];
    u32 publicId;
    u8 pad010[0xE64 - 0x10];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
    u8 padE70[0xEDA - 0xE70];
    u8 syncCrossFlags;
    u8 padEDB;
    u32* syncSeqIdPtr;
    u8 padEE0[0x1868 - 0xEE0];
};

extern SEQ_INSTANCE* lbl_8064D39C;
extern SEQ_INSTANCE* lbl_8064D398;
extern SEQ_INSTANCE* lbl_8064D394;
extern void fn_801C21E8(u32);
extern void fn_801B244C(SEQ_INSTANCE*);

#define seqActiveRoot lbl_8064D39C
#define seqPausedRoot lbl_8064D398
#define seqFreeRoot lbl_8064D394
#define voiceKillSound fn_801C21E8
#define ResetNotes fn_801B244C

static SEQ_INSTANCE seqInstance[8];

static inline u32 seqGetPrivateId(u32 seqId)
{
    SEQ_INSTANCE* si;
    for (si = seqActiveRoot; si != 0; si = si->next) {
        if (si->publicId == (seqId & ~0x80000000)) {
            return si->index | seqId & 0x80000000;
        }
    }
    for (si = seqPausedRoot; si != 0; si = si->next) {
        if (si->publicId == (seqId & ~0x80000000)) {
            return si->index | seqId & 0x80000000;
        }
    }
    return 0xffffffff;
}

static inline void KillNotes(SEQ_INSTANCE* seq)
{
    NOTE* n;
    u32 i;

    for (i = 0; i < 2; i++) {
        for (n = seq->noteUsed[i]; n != 0; n = n->next) {
            voiceKillSound(n->id);
        }
    }

    for (n = seq->noteKeyOff; n != 0; n = n->next) {
        voiceKillSound(n->id);
    }
}

static inline void StartPause(SEQ_INSTANCE* si)
{
    if (si->prev != 0) {
        si->prev->next = si->next;
    } else {
        seqActiveRoot = si->next;
    }

    if (si->next != 0) {
        si->next->prev = si->prev;
    }

    if ((si->next = seqPausedRoot) != 0) {
        seqPausedRoot->prev = si;
    }

    si->prev = 0;
    seqPausedRoot = si;
    si->state = 2;
}

void fn_801B35BC(u32 seqId)
{
    SEQ_INSTANCE* si;
    seqId = seqGetPrivateId(seqId);

    if (seqId == 0xffffffff) {
        return;
    }

    if ((seqId & 0x80000000) == 0) {
        si = &seqInstance[seqId];
        if (si->state == 1) {
            StartPause(si);
            KillNotes(si);
            ResetNotes(si);
        }
    } else {
        si = &seqInstance[seqId & ~0x80000000];
        if (si->state != 0) {
            si->syncCrossFlags |= 8;
        }
    }
}
