typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Source {
    u8 padding00[8];
    u32 value08;
} Source;

typedef struct Entry {
    u8 active;
    u8 padding01[15];
    Source* source;
    u8 work[60];
    void* handle;
    u32 position;
    u32 limit;
    void* buffer;
    u32 chunk_size;
    u32 buffer_size;
    u8 half;
    u8 padding69[3];
    int reset_pending;
    int field70;
    int pending;
    int stopped;
} Entry;

extern void* memset(void*, int, unsigned int);
extern void fn_801AE368(Entry*);
extern void fn_801AE6B0(void);
extern void fn_801B9E7C(void*, u32, u32, int, int);
extern int fn_80213704(void*, void*, u32, u32, void (*)(void), int);

int fn_801AE3C8(Entry* entry)
{
    register u32 amount;
    void* destination;
    void* selected;
    u32 position;
    unsigned long half_size;

    half_size = entry->chunk_size >> 1;
    amount = half_size;
    selected = entry->half != 0
                   ? (u8*)entry->buffer + half_size
                   : entry->buffer;
    destination = selected;

    if (entry->position + amount > entry->limit) {
        if (entry->limit > entry->position) {
            amount = entry->limit - entry->position;
            memset((u8*)destination + amount, 0,
                   half_size - amount);
        } else {
            memset(destination, 0, half_size);
            fn_801B9E7C(entry->handle,
                        entry->half != 0 ? entry->buffer_size >> 1 : 0,
                        entry->buffer_size >> 1, 0, 0);
            amount = 0;
        }
    }

    if (amount != 0) {
        position = entry->position;
        if (entry->pending == 1) {
            return 0;
        }

        while (fn_80213704(entry->work, destination, amount,
                          entry->source->value08 + position, fn_801AE6B0, 2) == 0) {
        }
        entry->pending = 1;
        entry->position += amount;
    } else if (entry->reset_pending != 0) {
        entry->reset_pending = 0;
    } else {
        fn_801AE368(entry);
    }

    entry->half ^= 1;
    return 1;
}
