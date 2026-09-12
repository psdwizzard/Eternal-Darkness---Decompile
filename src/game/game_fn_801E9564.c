typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry110 {
    u8 pad00[0x104];
    u32 data104;
    u32 data108;
    u32 data10C;
} Entry110;

typedef struct Entry0C {
    u8 pad00[8];
    Entry110* entry08;
} Entry0C;

typedef struct Header {
    u16 type;
    u16 count04;
    Entry110* entries;
    u16 count08;
    u8 pad0A[2];
    Entry0C* links;
} Header;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_80265B74[];
extern char lbl_80265B98[];

/* NonMatching: behavior-complete, size-exact reconstruction. GC/1.3 assigns
 * the entry pointer and field size to r4/r3; retail uses r3/r4. */
u32 fn_801E9564(const u8* source, Header* header)
{
    u32 offset = 0;
    Entry110* entry;
    u16 i;
    Entry110* entries;

    *header = *(const Header*)source;
    offset += sizeof(Header);
    fn_801E9124(&offset);

    if (header->type != 0x10) {
        fn_80155BB0(lbl_80265B74, lbl_80265B98, header->type, 0x10);
    }
    if (header->entries != 0) {
        u32 size = (u32)header->entries;
        header->entries = (Entry110*)(source + offset);
        offset += size;
    }
    {
    entries = header->entries;
    for (i = 0; i < header->count04; i++) {
        entry = &entries[i];
        if (entry->data104 != 0) {
            u32 size = entry->data104;
            entry->data104 = (u32)(source + offset);
            offset += size;
        }
        if (entry->data108 != 0) {
            u32 size = entry->data108;
            entry->data108 = (u32)(source + offset);
            offset += size;
        }
        if (entry->data10C != 0) {
            u32 size = entry->data10C;
            entry->data10C = (u32)(source + offset);
            offset += size;
        }
    }
    }
    if (header->links != 0) {
        u32 size = (u32)header->links;
        header->links = (Entry0C*)(source + offset);
        offset += size;
        for (i = 0; i < header->count08; i++) {
            header->links[i].entry08 = &header->entries[i];
        }
    }
    return offset;
}
