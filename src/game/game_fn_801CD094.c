typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x20];
    u32 cursor;
    u8 pad24[0x54];
    u32 base;
    u8 pad7C[0x14];
    u8 mode;
    u8 pad91[0x5B];
    u8 state;
    u8 padED[7];
} Entry;

extern Entry* lbl_8064D4AC;

u32 fn_801CD094(u32 index)
{
    Entry* entries = lbl_8064D4AC;
    Entry* entry = &lbl_8064D4AC[index];
    u32 offset = index * sizeof(Entry);

    if (entry->state != 2) {
        return 0;
    }

    switch (entry->mode) {
    case 0:
    case 1:
    case 4:
    case 5: {
        Entry* current = (Entry*)((u8*)entries + offset);
        u32 result = (current->cursor - current->base * 2) >> 4;
        u32 remainder = current->cursor & 0xF;
        result *= 14;
        if (remainder < 2) {
            return result;
        }
        return (remainder + result) - 2;
    }
    case 3:
        return entry->cursor - entry->base;
    case 2:
        return entry->cursor - (entry->base >> 1);
    }
}
