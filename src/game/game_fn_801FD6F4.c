typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    u8 pad04[0x24];
    u8 active;
    u8 pad29[0x53];
} Entry;

extern Entry* lbl_8064D7D0;

Entry* fn_801FD6F4(u32 id)
{
    Entry* result = 0;
    Entry* entry = lbl_8064D7D0;
    int i;

    for (i = 0; i < 12; entry++, i++) {
        if (entry->id == id && entry->active && entry->id != 0) {
            result = entry;
            break;
        }
    }
    return result;
}
