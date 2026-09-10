typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SND_EMITTER {
    u8 pad00[0x40];
    void* group;
} SND_EMITTER;

typedef struct RUN_LIST {
    struct RUN_LIST* next;
    float vol;
    SND_EMITTER* em;
} RUN_LIST;

typedef struct START_LIST {
    struct START_LIST* next;
    float vol;
    float xPan;
    float yPan;
    float zPan;
    float pitch;
    SND_EMITTER* em;
} START_LIST;

typedef struct START_GROUP {
    void* id;
    START_LIST* list;
    RUN_LIST* running;
    u16 numRunning;
    u16 pad0E;
} START_GROUP;

static u8 s3dPad[0x50];
static START_GROUP startGroup[64];
static START_LIST startListNum[64];
static RUN_LIST runList[64];
extern u8 lbl_8064D4D3;
extern u8 lbl_8064D4D5;
#define startGroupNum lbl_8064D4D3
#define runListNum lbl_8064D4D5

void fn_801C9A08(SND_EMITTER* emitter, float vol)
{
    START_GROUP* group;
    RUN_LIST* node;
    RUN_LIST* prev;
    int groupCount;
    int groupIndex;

    group = startGroup;
    groupCount = startGroupNum;
    for (groupIndex = 0; groupIndex < groupCount; groupIndex++) {
        if (emitter->group == group->id) {
            break;
        }
        group++;
    }

    if (groupIndex == groupCount) {
        startGroup[groupIndex].list = (START_LIST*)0x0;
        startGroup[groupIndex].running = (RUN_LIST*)0x0;
        startGroup[groupIndex].numRunning = 0;
        startGroup[groupIndex].id = emitter->group;
        startGroupNum++;
    }

    startGroup[groupIndex].numRunning++;
    node = startGroup[groupIndex].running;
    prev = (RUN_LIST*)0x0;
    while (node != (RUN_LIST*)0x0) {
        if (node->vol > vol) {
            break;
        }
        prev = node;
        node = node->next;
    }

    if (prev == (RUN_LIST*)0x0) {
        startGroup[groupIndex].running = &runList[runListNum];
    } else {
        prev->next = &runList[runListNum];
    }
    {
        RUN_LIST* newNode = &runList[runListNum];
        newNode->next = node;
        newNode->em = emitter;
    }
    runList[runListNum++].vol = vol;
}
