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
extern u8 lbl_8064D4D4;
#define startGroupNum lbl_8064D4D3
#define startListNumnum lbl_8064D4D4

int fn_801C9B1C(SND_EMITTER* emitter, float vol, float xPan, float yPan, float zPan, float pitch)
{
    START_GROUP* group;
    START_LIST* scan;
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
        if ((u32)groupCount == 64) {
            return 0;
        }
        startGroup[groupIndex].list = (START_LIST*)0x0;
        startGroup[groupIndex].running = (RUN_LIST*)0x0;
        startGroup[groupIndex].numRunning = 0;
        startGroup[groupIndex].id = emitter->group;
        startGroupNum++;
    }

    if (startListNumnum == 64) {
        return 0;
    }

    if ((scan = startGroup[groupIndex].list) != (START_LIST*)0x0) {
        while (scan->next != (START_LIST*)0x0) {
            if (scan->vol < vol) {
                break;
            }
            scan = scan->next;
        }
        startListNum[startListNumnum].next = scan->next;
        scan->next = &startListNum[startListNumnum];
    } else {
        startListNum[startListNumnum].next = startGroup[groupIndex].list;
        startGroup[groupIndex].list = &startListNum[startListNumnum];
    }

    {
        START_LIST* newNode = &startListNum[startListNumnum];
        newNode->em = emitter;
        newNode->pitch = pitch;
        newNode->xPan = xPan;
        newNode->yPan = yPan;
        newNode->zPan = zPan;
    }
    startListNum[startListNumnum++].vol = vol;
    return 1;
}
