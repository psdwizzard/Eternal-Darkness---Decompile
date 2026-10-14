/* fn_8022F700 (0x8022F700, 92 bytes): initialises a memory heap region. */

typedef unsigned char u8;
typedef unsigned int u32;

extern void* memset(void*, int, unsigned long);

typedef struct HeapHeader {
    u8 pad00[0x18];
    u32 magic;
    u8 pad1C[0x4];
} HeapHeader;

extern u32 lbl_8064DC0C;
extern u32 lbl_8064DC20;
extern u8* lbl_8064DC24;
extern u32 lbl_8064DC28;
extern HeapHeader* lbl_8064DC2C;

void fn_8022F700(HeapHeader* base, register u32 size) {
    register u32 clearSize;
    register unsigned long work;
    register HeapHeader* header;

    /* ASM: mr/li retain the retail argument move and zero-load ordering;
     * C emits addi for the copy and schedules li between the global stores. */
    asm {
        mr clearSize, size
        li r4, 0
        mr work, r4
    }
    lbl_8064DC2C = base;
    lbl_8064DC28 = size;
    memset(base, (int)work, clearSize);
    /* Reuse the zero-fill argument register for the heap-header reload. */
    work = (unsigned long)lbl_8064DC2C;
    header = (HeapHeader*)work;
    lbl_8064DC20 = size;
    lbl_8064DC24 = (u8*)header + 0x20;
    lbl_8064DC0C = size;
    header->magic = 0xBAADF00D;
}
