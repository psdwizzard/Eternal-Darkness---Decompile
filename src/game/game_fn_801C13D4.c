typedef unsigned int u32;

typedef struct VID_LIST {
    struct VID_LIST* next;
    struct VID_LIST* prev;
    u32 vid;
    u32 root;
} VID_LIST;

typedef struct SYNTH_VOICE {
    unsigned char pad_000[0xF4];
    u32 id;
    VID_LIST* vidList;
    VID_LIST* vidMasterList;
} SYNTH_VOICE;

extern u32 vidCurrentId;
extern VID_LIST* vidRoot;
extern VID_LIST* vidFree;

u32 vidMakeNew(SYNTH_VOICE* s, u32 returnNewId)
{
    u32 nextId;
    VID_LIST* cursor;
    VID_LIST* node;
    VID_LIST* prev;
    VID_LIST* freeNode;

    do {
        nextId = vidCurrentId;
        vidCurrentId = nextId + 1;
    } while (nextId == 0xffffffffU);

    cursor = vidRoot;
    prev = 0;
    while ((node = cursor) != 0) {
        if (node->vid > nextId) {
            break;
        }
        if (node->vid == nextId) {
            do {
                nextId = vidCurrentId;
                vidCurrentId = nextId + 1;
            } while (nextId == 0xffffffffU);
        }
        prev = node;
        cursor = node->next;
    }

    if ((freeNode = vidFree) == 0) {
        return 0xffffffffU;
    }
    if ((vidFree = vidFree->next) != 0) {
        vidFree->prev = 0;
    }
    if (prev == 0) {
        vidRoot = freeNode;
    } else {
        prev->next = freeNode;
    }
    freeNode->prev = prev;
    freeNode->next = node;
    if (node != 0) {
        node->prev = freeNode;
    }
    freeNode->vid = nextId;
    freeNode->root = s->id;
    s->vidMasterList = ((u32)returnNewId != 0) ? freeNode : 0;
    s->vidList = freeNode;
    if ((u32)returnNewId != 0) {
        return nextId;
    }
    return s->id;
}
