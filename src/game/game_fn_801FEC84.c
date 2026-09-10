typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EntryA {
    u8 pad_0[8];
    u32 data;
    u8 pad_C[0x17];
    u8 relocated;
} EntryA;

typedef struct EntryB {
    u8 pad_0[2];
    u8 relocated;
    u8 pad_3[5];
    u32 data;
} EntryB;

typedef struct EntryPair {
    EntryA* first;
    EntryB* second;
} EntryPair;

typedef struct Header {
    u32 field_0;
    u32 count;
    EntryPair* entries;
} Header;

void fn_801FEC84(Header* header)
{
    u16 i;

    header->entries = (EntryPair*)((u32)header->entries + (u32)header);
    for (i = 0; i < header->count; i++) {
        if (header->entries[i].first != 0) {
            header->entries[i].first =
                (EntryA*)((u8*)header + (u32)header->entries[i].first);
            if (header->entries[i].first->relocated == 0) {
                header->entries[i].first->data =
                    (u32)header + header->entries[i].first->data;
                header->entries[i].first->relocated = 1;
            }
        }

        if (header->entries[i].second != 0) {
            header->entries[i].second =
                (EntryB*)((u8*)header + (u32)header->entries[i].second);
            if (header->entries[i].second->relocated == 0) {
                header->entries[i].second->data =
                    (u32)header + header->entries[i].second->data;
                header->entries[i].second->relocated = 1;
            }
        }
    }
}
