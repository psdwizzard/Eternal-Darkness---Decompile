typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct NOTE NOTE;
struct NOTE {
    NOTE* next;
    NOTE* prev;
    u32 id;
    s32 endTime;
    u8 section;
    u8 pad11[3];
};

typedef struct SECTION {
    struct {
        s32 high;
        s32 low;
    } time[2];
    u8 pad10[0x38 - 0x10];
} SECTION;

typedef struct SEQ_INSTANCE {
    u8 pad000[0xE64];
    NOTE* noteUsed[2];
    NOTE* noteKeyOff;
    u8 padE70[0x150C - 0xE70];
    SECTION section[15];
} SEQ_INSTANCE;

extern SEQ_INSTANCE* lbl_8064D380;
extern void fn_801B80D8(u32);

#define cseq lbl_8064D380
#define synthSendKeyOff fn_801B80D8

u32 fn_801B261C(void)
{
    NOTE* note;
    u32 i;

    for (i = 0; i < 2; i++) {
        if ((note = cseq->noteUsed[i]) != 0) {
            while (note->endTime <= cseq->section[note->section].time[i].high) {
                synthSendKeyOff(note->id);

                if ((cseq->noteUsed[i] = note->next) != 0) {
                    cseq->noteUsed[i]->prev = 0;
                }

                if ((note->next = cseq->noteKeyOff) != 0) {
                    cseq->noteKeyOff->prev = note;
                }
                cseq->noteKeyOff = note;
                if ((note = cseq->noteUsed[i]) == 0) {
                    break;
                }
            }
        }
    }

    return cseq->noteUsed[0] != 0 || cseq->noteUsed[1] != 0;
}
