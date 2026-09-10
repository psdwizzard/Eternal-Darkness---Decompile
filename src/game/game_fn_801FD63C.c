typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Actor {
    u8 pad00[0x2A];
    u16 flags;
    u8 pad2C[8];
    u8 priority;
} Actor;

typedef struct Entry {
    u32 id;
    u8 pad04[0x24];
    u8 active;
} Entry;

extern Entry* fn_801FD3F8(u8, u8);
extern void fn_801FE2A8(Actor*, u32);

u32 fn_801FD63C(Actor* actor)
{
    u32 result = 0;
    Entry* entry = fn_801FD3F8(actor->priority, actor->flags & 0x20);

    if (entry != 0) {
        entry->active = 1;
        fn_801FE2A8(actor, entry->id);
        result = entry->id;
    }
    return result;
}
