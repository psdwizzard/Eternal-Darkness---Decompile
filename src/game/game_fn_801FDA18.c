typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x1E];
    u16 state;
    unsigned char pad24[0x4C];
    u16 type;
} Entry;

extern Entry* fn_801FD6F4(u32);
extern int fn_801FE05C(u32);

int fn_801FDA18(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0 && entry->type == 1 && fn_801FE05C(id)) {
        entry->state = 2;
    }
    return 0;
}
