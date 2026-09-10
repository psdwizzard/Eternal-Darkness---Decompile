typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Header {
    u32 count;
    u32 index;
    u32 refresh;
    u32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u16 version;
    u8 pad1E[0x22];
} Header;

typedef struct Record {
    u16 flags;
    u8 first_index;
    u8 second_index;
    u8 pad04[0xC];
} Record;

typedef struct Block {
    u8 pad00[0x70];
    struct Block* link70;
    struct Block* link74;
    u8 pad78[0x10];
} Block;

extern u32 lbl_8064D7BC;
extern u32 lbl_8064C3A8;
extern u32 lbl_8064C3A0;
extern u32 lbl_8064D798;
extern u32 lbl_8064C3A4;
extern u32 lbl_8064D79C;
extern u32 lbl_8064D18C;
typedef struct BlockGlobals {
    Block first[12];
    Block second[12];
    Block primary;
    Block secondary;
    u8 entries[1];
} BlockGlobals;
extern BlockGlobals lbl_8063C6B8;
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_801FBB84(Record*, void*);
extern u16 fn_801FB6A4(void*, Block*, int, int);
extern void fn_801F85A4(void);
extern void fn_801FA354(void);

u32 fn_801FAD4C(void* input)
{
    Header header;
    Record record;
    int valid = 1;
    u16 offset = 0x40;
    int i;
    u8* entry;
    BlockGlobals* globals = &lbl_8063C6B8;

    memcpy(&header, input, 0x40);
    if (header.version != lbl_8064D18C) {
        valid = 0;
    }
    if (valid) {
        lbl_8064D7BC = header.count;
        lbl_8064C3A8 = header.index;
        lbl_8064C3A0 = header.field0C;
        lbl_8064D798 = header.field10;
        lbl_8064C3A4 = header.field14;
        lbl_8064D79C = header.field18;
    }

    entry = globals->entries;
    for (i = 0; i < (int)lbl_8064D7BC; i++, entry += 0x14) {
        memcpy(&record, (u8*)input + offset, 0x10);
        offset += 0x10;
        if (valid) {
            fn_801FBB84(&record, entry);
        }
        if (record.flags & 1) {
            offset += fn_801FB6A4((u8*)input + offset,
                                  &globals->second[record.first_index], 0, valid);
        }
        if (record.flags & 2) {
            offset += fn_801FB6A4((u8*)input + offset,
                                  &globals->first[record.second_index], 1, valid);
        }
    }

    offset += fn_801FB6A4((u8*)input + offset, &globals->primary, 0, valid);
    globals->primary.link70 = &globals->second[lbl_8064C3A8];
    globals->primary.link74 = &globals->secondary;
    offset += fn_801FB6A4((u8*)input + offset,
                          &globals->second[lbl_8064C3A8], 0, valid);
    offset += fn_801FB6A4((u8*)input + offset, &globals->secondary, 1, valid);
    globals->secondary.link70 = &globals->first[lbl_8064C3A8];
    globals->secondary.link74 = 0;
    offset += fn_801FB6A4((u8*)input + offset,
                          &globals->first[lbl_8064C3A8], 1, valid);

    for (i = 0; i < 12; i++) {
        globals->second[i].link74 = &globals->first[i];
        globals->first[i].link74 = 0;
    }
    if (header.refresh != 0) {
        fn_801F85A4();
        fn_801FA354();
    }
    return (offset + 0x1F) & ~0x1F;
}
