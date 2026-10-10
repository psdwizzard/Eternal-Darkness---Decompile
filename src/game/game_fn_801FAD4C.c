typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Header {
    u32 count;
    u32 index;
    int refresh;
    u32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u16 version;
    u8 pad1E[0x22];
} Header;

typedef struct PackedObject {
    u16 flags;
    u8 first_index;
    u8 second_index;
    float x;
    float y;
    u32 value;
} Record;

typedef struct Object {
    float x;
    float y;
    void* first;
    void* second;
    u32 value;
} Object;

typedef struct PackedRecord PackedRecord;
typedef struct OutputRecord OutputRecord;

/* Link fields within the 0x88-byte unpacked record. */
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
extern int lbl_8064D18C;
typedef struct BlockGlobals {
    Block first[12];
    Block second[12];
    Block primary;
    Block secondary;
    Object entries[5];
} BlockGlobals;
extern BlockGlobals lbl_8063C6B8;
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_801FBB84(Record*, Object*);
extern u16 fn_801FB6A4(PackedRecord*, OutputRecord*, int, int);
extern int fn_801F85A4(void);
extern void fn_801FA354(void);

static inline void initialize_links(Block* first, Block* second)
{
    int i;
    for (i = 0; i < 12; i++) {
        second[i].link74 = &first[i];
        first[i].link74 = 0;
    }
}

u32 fn_801FAD4C(void* input)
{
    Header header;
    Record record;
    Object* entry;
    int i;
    u16 offset;
    register int valid = 1;
    register BlockGlobals* globals = &lbl_8063C6B8;

    memcpy(&header, input, 0x40);
    offset = 0x40;
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
    for (i = 0; i < (int)lbl_8064D7BC; entry++, i++) {
        memcpy(&record, (u8*)input + offset, 0x10);
        offset += 0x10;
        if (valid) {
            fn_801FBB84(&record, entry);
        }
        if (record.flags & 1) {
            Block* block = globals->second;
            block = record.first_index + block;
            offset += fn_801FB6A4((PackedRecord*)((u8*)input + offset),
                              (OutputRecord*)block, 0, valid);
        }
        if (record.flags & 2) {
            Block* block = globals->first;
            block = (Block*)((u8*)block + record.second_index * sizeof(Block));
            offset += fn_801FB6A4((PackedRecord*)((u8*)input + offset),
                              (OutputRecord*)block, 1, valid);
        }
    }

    offset += fn_801FB6A4((PackedRecord*)((u8*)input + offset),
                              (OutputRecord*)&globals->primary, 0, valid);
    {
        register u32 index = lbl_8064C3A8;
        register Block* base;
        register Block* next;
        register Block* current;
        register u16 sourceOffset = offset;
        register u32 stride;
        register int copy;
        /* ASM: addi, mr, mulli, and clrlwi keep the pooled bases and
         * 16-bit cursor separate. C folds the field addresses and assigns
         * their registers to the index without these boundaries. */
        asm {
            addi base, globals, 0x660
            addi next, globals, 0xd48
            mr current, index
            mulli stride, current, 0x88
            addi current, globals, 0xcc0
            mr current, current
            clrlwi sourceOffset, sourceOffset, 16
        }
        current->link74 = next;
        /* ASM: mr reserves the copy-flag argument register before the
         * indexed address; C otherwise reuses it for the stride. */
        asm { mr copy, valid }
        base = (Block*)((u8*)base + stride);
        current->link70 = base;
        offset += fn_801FB6A4((PackedRecord*)((u8*)input + sourceOffset),
                              (OutputRecord*)base, 0, copy);
    }
    offset += fn_801FB6A4((PackedRecord*)((u8*)input + offset),
                              (OutputRecord*)&globals->secondary, 1, valid);
    {
        register u32 index = lbl_8064C3A8;
        register Block* base;
        register Block* next;
        register Block* current;
        register u16 sourceOffset = offset;
        register u32 stride;
        register int copy;
        /* ASM: addi, li, mr, mulli, and clrlwi keep the pooled bases and
         * 16-bit cursor separate. C folds the field addresses and assigns
         * their registers to the index without these boundaries. */
        asm {
            addi base, globals, 0
            li next, 0
            mr current, index
            mulli stride, current, 0x88
            addi current, globals, 0xd48
            mr current, current
            clrlwi sourceOffset, sourceOffset, 16
        }
        current->link74 = next;
        /* ASM: mr reserves the copy-flag argument register before the
         * indexed address; C otherwise reuses it for the stride. */
        asm { mr copy, valid }
        base = (Block*)((u8*)base + stride);
        current->link70 = base;
        offset += fn_801FB6A4((PackedRecord*)((u8*)input + sourceOffset),
                              (OutputRecord*)base, 1, copy);
    }

    initialize_links(globals->first, globals->second);
    if (header.refresh != 0) {
        fn_801F85A4();
        fn_801FA354();
    }
    return (u16)(offset + 0x1F) & ~0x1F;
}
