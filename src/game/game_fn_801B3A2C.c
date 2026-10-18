typedef unsigned char u8;
typedef unsigned short u16;
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
            return node->type | (value & 0x80000000U);
        }
        node = node->next;
    }
    node = seqPausedRoot;
    while (node != 0) {
        if (node->key == key) {
            return node->type | (value & 0x80000000U);
        }
        node = node->next;
    }
    return -1;
}

u8* seqSpeed(u32 handle, u16 value)
{
    u8* base = (u8*)seqNote;
    u32 id = resolve_handle(handle);
    u8* entry;
    u32 i;

    if ((id & 0x80000000U) == 0) {
        entry = base + id * sizeof(Entry);
        for (i = 0; i < 16; i++) {
            *(u16*)(entry + 0x291A + i * 0x38) = value;
        }
    } else {
        entry = base + (id & 0x7FFFFFFF) * sizeof(Entry);
        entry[0x22DA] |= 0x20;
        *(u16*)(entry + 0x22D8) = value;
    }
    return entry;
}
