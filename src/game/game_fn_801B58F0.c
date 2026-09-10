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
    u8 pad0A[0x1868 - 0xA];
};

static NOTE seqNote[256];
static SEQ_INSTANCE seqInstance[8];
static u16 seqMIDIPriority[8][16];

extern SEQ_INSTANCE* lbl_8064D39C;
extern SEQ_INSTANCE* lbl_8064D398;
extern SEQ_INSTANCE* lbl_8064D394;
extern NOTE* lbl_8064D384;
extern u32 lbl_8064D390;

#define seqActiveRoot lbl_8064D39C
#define seqPausedRoot lbl_8064D398
#define seqFreeRoot lbl_8064D394
#define noteFree lbl_8064D384
#define seq_next_id lbl_8064D390

static inline void ClearNotes(void)
{
    NOTE* ln = 0;
    s32 i;

    noteFree = &seqNote[0];
    for (i = 0; i < 256; i++) {
        seqNote[i].prev = ln;
        if (ln != 0) {
            ln->next = &seqNote[i];
        }
        ln = &seqNote[i];
    }

    ln->next = 0;
}

static inline void InitPublicIds(void)
{
    seq_next_id = 0;
}

void fn_801B58F0(void)
{
    u32 i;
    u32 j;

    seqActiveRoot = 0;
    seqPausedRoot = 0;
    for (i = 0; i < 8; i++) {
        if (i == 0) {
            seqFreeRoot = &seqInstance[i];
            seqInstance[i].prev = 0;
        } else {
            seqInstance[i - 1].next = &seqInstance[i];
            seqInstance[i].prev = &seqInstance[i - 1];
        }
        seqInstance[i].index = i;
        seqInstance[i].state = 0;
        for (j = 0; j < 0x10; j++) {
            seqMIDIPriority[i][j] = 0xffff;
        }
    }
    seqInstance[i - 1].next = 0;
    ClearNotes();
    InitPublicIds();
}
