typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Owner Owner;
struct Owner {
    Owner* next;
    Owner* prev;
    u8 state;
    u8 type;
    u8 pad0A[2];
    u32 key;
    u8 pad10[0x1858];
};

extern Owner lbl_8060D420[];
extern Owner* seqPausedRoot;
extern Owner* seqActiveRoot;

static inline int resolve_handle(u32 value)
{
    u32 key = value & 0x7FFFFFFF;
    Owner* node = seqActiveRoot;

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

void seqContinue(u32 handle)
{
    u32 id = resolve_handle(handle);
    Owner* owner;

    if ((id & 0x80000000U) == 0) {
        owner = &lbl_8060D420[id];
        if (owner->state != 2) {
            return;
        }
        if (owner->prev != 0) {
            owner->prev->next = owner->next;
        } else {
            seqPausedRoot = owner->next;
        }
        if (owner->next != 0) {
            owner->next->prev = owner->prev;
        }
        if ((owner->next = seqActiveRoot) != 0) {
            seqActiveRoot->prev = owner;
        }
        owner->prev = 0;
        seqActiveRoot = owner;
        owner->state = 1;
    } else {
        lbl_8060D420[id & 0x7FFFFFFF].pad10[0xECA] &= ~8;
    }
}
