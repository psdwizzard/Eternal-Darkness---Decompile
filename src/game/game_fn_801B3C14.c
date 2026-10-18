typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    u8 state;
    u8 type;
    u8 pad0A[2];
    u32 key;
};

typedef struct Entry Entry;
struct Entry { u8 data[0x1868]; };

extern Entry seqNote[];
extern Node* seqPausedRoot;
extern Node* seqActiveRoot;

static inline u32 resolve_handle(u32 value)
{
    u32 key = value & 0x7FFFFFFF;
    Node* node = seqActiveRoot;

    while (node != 0) {
        if (node->key == key) {
            key = node->type;
            return key | (value & 0x80000000U);
        }
        node = node->next;
    }
    node = seqPausedRoot;
    while (node != 0) {
        if (node->key == key) {
            key = node->type;
            return key | (value & 0x80000000U);
        }
        node = node->next;
    }
    return -1;
}

void seqMute(u32 handle, u32 value1, u32 value2)
{
    u8* base = (u8*)seqNote;
    u32 id = resolve_handle(handle);
    u8* entry;

    if (id == (u32)-1) {
        return;
    }
    if ((id & 0x80000000U) == 0) {
        entry = base + id * sizeof(Entry);
        *(u32*)(entry + 0x151C) = value1;
        *(u32*)(entry + 0x1520) = value2;
    } else {
        entry = base + (id & 0x7FFFFFFF) * sizeof(Entry);
        entry[0x22DA] |= 0x10;
        *(u32*)(entry + 0x22D0) = value1;
        *(u32*)(entry + 0x22D4) = value2;
    }
}
