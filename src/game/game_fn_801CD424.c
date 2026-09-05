typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xE8];
    u32 handle;
    u8 active;
    u8 padED[7];
} Entry;

extern Entry* lbl_8064D4AC;

u32 fn_801CD424(u32 index)
{
    Entry* entry = &lbl_8064D4AC[index];
    if (entry->active == 0) {
        return -1;
    }
    return entry->handle;
}
