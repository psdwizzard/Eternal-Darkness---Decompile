typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SynthDelayedNode {
    struct SynthDelayedNode* next;
    struct SynthDelayedNode* prev;
    u8 unk8;
    u8 jobTabIndex;
    u8 padA[2];
} SynthDelayedNode;

typedef struct SynthJobTab {
    SynthDelayedNode* lowPrecision;
    SynthDelayedNode* event;
    SynthDelayedNode* zeroOffset;
} SynthJobTab;

typedef struct SynthState {
    u8 pad000[0x240];
    SynthJobTab jobs[32];
    u8 pad3C0[0xE20 - 0x3C0];
} SynthState;

extern SynthState lbl_80619860;
#define synthState lbl_80619860
extern u8 lbl_8064D3A1;

#define synthJobTable synth->jobs
#define synthJobTableIndex lbl_8064D3A1

void fn_801B775C(SynthDelayedNode* fade, int mode, u32 delay)
{
    SynthDelayedNode* newJq;
    SynthDelayedNode** root;
    u8 jobTabIndex;
    SynthJobTab* jobTab;
    SynthState* synth = &synthState;

    jobTabIndex = ((delay / 256) + synthJobTableIndex) & 0x1F;
    jobTab = &synthJobTable[jobTabIndex];

    switch (mode) {
    case 0:
        newJq = fade;
        if (newJq->jobTabIndex != 0xFF) {
            if (newJq->jobTabIndex == jobTabIndex) {
                return;
            }
            if (newJq->next != 0) {
                newJq->next->prev = newJq->prev;
            }
            if (newJq->prev != 0) {
                newJq->prev->next = newJq->next;
            } else {
                synthJobTable[newJq->jobTabIndex].lowPrecision = newJq->next;
            }
        }
        root = &jobTab->lowPrecision;
        break;
    case 1:
        newJq = fade + 1;
        if (newJq->jobTabIndex != 0xFF) {
            if (newJq->jobTabIndex == jobTabIndex) {
                return;
            }
            if (newJq->next != 0) {
                newJq->next->prev = newJq->prev;
            }
            if (newJq->prev != 0) {
                newJq->prev->next = newJq->next;
            } else {
                synthJobTable[newJq->jobTabIndex].zeroOffset = newJq->next;
            }
        }
        root = &jobTab->zeroOffset;
        break;
    case 2:
        newJq = fade + 2;
        if (newJq->jobTabIndex != 0xFF) {
            return;
        }
        root = &jobTab->event;
        break;
    default:
        break;
    }

    newJq->jobTabIndex = jobTabIndex;
    if ((newJq->next = *root) != 0) {
        (*root)->prev = newJq;
    }
    newJq->prev = 0;
    *root = newJq;
}
