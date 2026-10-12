typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The 0x98-byte header describes the 21 serialized blocks that follow it. */
typedef struct SaveHeader {
    u8 version;
    u8 chapter;
    u16 room;
    u32 game;
    u64 playTime;
    u32 value10;
    u8 saveCount;
    u8 value15;
    u16 value16;
    u16 sizes[21];       /* 0x18 */
    u32 checksums[21];   /* 0x44 */
} SaveHeader;

typedef struct GameState {
    u8 pad0[0xC];
    u32 game;
    u8 pad10[4];
    u8 data[0x1900];
    u8 chapter;
    u8 pad1915;
    u16 dataSize;
    u8 pad1918[2];
    u8 saveCount;
} GameState;

typedef struct SavedBlocks {
    u8 pad0[0x150];
    void* block150;
    void* block154;
    void* block158;
    void* block15C;
    u16 size160;
    u16 size162;
    u16 size164;
    u16 size166;
} SavedBlocks;

extern void* memcpy(void*, const void*, unsigned long);
extern u64 fn_801E8E2C(void);
extern void fn_801570AC(void*);
extern void fn_802021EC(void*);
extern int fn_80155D9C(int);
extern void fn_801E79A0(void*, int);
extern u32 fn_801E74B8(const u32*, void*);
extern u32 fn_801E7454(const u8*, u32);
extern int fn_800877B8(void*);
extern int fn_800E5050(void*);
extern int fn_801F4E38(u8*);
extern int fn_800B05F8(u8*);
extern int fn_80028D54(void*);
extern int fn_800712D8(void*);
extern int fn_8016B1D0(void*);
extern u32 fn_801FABA4(u8*, int);
extern int fn_801F668C(void*);
extern u16 fn_801E8FAC(u8*);
extern u32 fn_801A8168(void*);
extern unsigned long fn_8011E918(void*);
/* This wrapper forwards its buffer and return value to fn_801AD8F8. */
extern int fn_801A9A00(void*);
extern int fn_80117A7C(void*);
extern int fn_80111724(void*);

extern GameState lbl_803003C8;
extern SavedBlocks lbl_80332158;
extern u32* lbl_8024E388[3];
extern u32* lbl_8064C4E0;
extern int lbl_8064C578;
extern u32* lbl_8064D158;
extern int lbl_8064D184;
extern int lbl_8064D18C;
extern u32 lbl_8064D5A8;

int fn_800B09D0(u8* data, void* unused, int useSavedBlocks)
{
    SaveHeader header;
    int offset;
    u32 i;
    register u32 result;
    register u16 size;

    header.version = 0x6C;
    header.game = lbl_803003C8.game;
    header.playTime = fn_801E8E2C();
    header.chapter = lbl_803003C8.chapter;
    header.sizes[20] = lbl_803003C8.dataSize;
    header.room = lbl_8064D18C;
    header.value10 = lbl_8064D5A8;
    header.value16 = lbl_8064D184;
    if (lbl_803003C8.saveCount + 1 < 100) {
        lbl_803003C8.saveCount++;
    }
    header.saveCount = lbl_803003C8.saveCount;
    header.value15 = lbl_8064C578;
    fn_801570AC((void*)fn_802021EC);
    if (useSavedBlocks) {
        fn_80155D9C(0);
    }
    fn_801570AC((void*)fn_802021EC);
    fn_801E79A0(lbl_8064C4E0, 0x37E);

    result = fn_801E74B8(lbl_8064C4E0, data + 0x98);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[0] = size;
    header.checksums[0] = fn_801E7454(data + 0x98, header.sizes[0]);
    offset = header.sizes[0] + 0x98;
    for (i = 0; i < 3; i++) {
        header.sizes[i + 1] = fn_801E74B8(lbl_8024E388[i], data + (u16)offset);
        header.checksums[i + 1] = fn_801E7454(data + (u16)offset, header.sizes[i + 1]);
        offset += header.sizes[i + 1];
    }

    result = fn_801E74B8(lbl_8064D158, data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[4] = size;
    header.checksums[4] = fn_801E7454(data + (u16)offset, header.sizes[4]);
    offset += header.sizes[4];

    result = fn_800877B8(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[5] = size;
    header.checksums[5] = fn_801E7454(data + (u16)offset, header.sizes[5]);
    offset += header.sizes[5];

    result = fn_800E5050(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[6] = size;
    header.checksums[6] = fn_801E7454(data + (u16)offset, header.sizes[6]);
    offset += header.sizes[6];

    result = fn_801F4E38(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[7] = size;
    header.checksums[7] = fn_801E7454(data + (u16)offset, header.sizes[7]);
    offset += header.sizes[7];

    result = fn_800B05F8(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[8] = size;
    header.checksums[8] = fn_801E7454(data + (u16)offset, header.sizes[8]);
    offset += header.sizes[8];

    result = fn_80028D54(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[9] = size;
    header.checksums[9] = fn_801E7454(data + (u16)offset, header.sizes[9]);
    offset += header.sizes[9];

    result = fn_800712D8(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[10] = size;
    header.checksums[10] = fn_801E7454(data + (u16)offset, header.sizes[10]);
    offset += header.sizes[10];

    result = fn_8016B1D0(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[11] = size;
    header.checksums[11] = fn_801E7454(data + (u16)offset, header.sizes[11]);
    offset += header.sizes[11];

    /* This mode reuses the three cached blocks. */
    if (useSavedBlocks) {
        memcpy(data + (u16)offset, lbl_80332158.block15C, lbl_80332158.size166);
        header.sizes[12] = lbl_80332158.size166;
        header.checksums[12] = fn_801E7454(data + (u16)offset, header.sizes[12]);
        offset += header.sizes[12];

        memcpy(data + (u16)offset, lbl_80332158.block150, lbl_80332158.size160);
        header.sizes[13] = lbl_80332158.size160;
        header.checksums[13] = fn_801E7454(data + (u16)offset, header.sizes[13]);
        offset += header.sizes[13];

        memcpy(data + (u16)offset, lbl_80332158.block158, lbl_80332158.size164);
        header.sizes[14] = lbl_80332158.size164;
        header.checksums[14] = fn_801E7454(data + (u16)offset, header.sizes[14]);
        offset += header.sizes[14];
    } else {
        result = fn_801FABA4(data + (u16)offset, useSavedBlocks);
        /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
        asm { mr size, result }
        header.sizes[12] = size;
        header.checksums[12] = fn_801E7454(data + (u16)offset, header.sizes[12]);
        offset += header.sizes[12];

        result = fn_801F668C(data + (u16)offset);
        /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
        asm { mr size, result }
        header.sizes[13] = size;
        header.checksums[13] = fn_801E7454(data + (u16)offset, header.sizes[13]);
        offset += header.sizes[13];

        header.sizes[14] = fn_801E8FAC(data + (u16)offset);
        header.checksums[14] = fn_801E7454(data + (u16)offset, header.sizes[14]);
        offset += header.sizes[14];
    }

    result = fn_801A8168(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[15] = size;
    header.checksums[15] = fn_801E7454(data + (u16)offset, header.sizes[15]);
    offset += header.sizes[15];

    result = fn_8011E918(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[16] = size;
    header.checksums[16] = fn_801E7454(data + (u16)offset, header.sizes[16]);
    offset += header.sizes[16];

    result = fn_801A9A00(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[17] = size;
    header.checksums[17] = fn_801E7454(data + (u16)offset, header.sizes[17]);
    offset += header.sizes[17];

    result = fn_80117A7C(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[18] = size;
    header.checksums[18] = fn_801E7454(data + (u16)offset, header.sizes[18]);
    offset += header.sizes[18];

    result = fn_80111724(data + (u16)offset);
    /* ASM: mr keeps a separate size register; C coalesces it with the call result. */
    asm { mr size, result }
    header.sizes[19] = size;
    header.checksums[19] = fn_801E7454(data + (u16)offset, header.sizes[19]);
    offset += header.sizes[19];

    memcpy(data + (u16)offset, lbl_803003C8.data, header.sizes[20]);
    header.checksums[20] = fn_801E7454(data + (u16)offset, header.sizes[20]);
    offset += header.sizes[20];
    memcpy(data, &header, 0x98);
    if (useSavedBlocks) {
        fn_80155D9C(1);
    }
    return offset;
}
