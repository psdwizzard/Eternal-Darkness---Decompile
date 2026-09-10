typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x1E];
    u16 state;
    u16 threshold;
    s16 current;
} Entry;

extern Entry* fn_801FD6F4(u32);
extern int fn_801FE0B4(u32);

int fn_801FD958(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0 && entry->current >= entry->threshold && fn_801FE0B4(id)) {
        entry->state = 2;
    }
    return 0;
}
