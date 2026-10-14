/* fn_8022F700 (0x8022F700, 92 bytes): initialises a memory heap region. */

typedef unsigned char u8;
typedef unsigned int u32;

extern void* memset(void*, int, u32);

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

void fn_8022F700(HeapHeader* base, u32 size) {
    lbl_8064DC2C = base;
    lbl_8064DC28 = size;
    memset(base, 0, size);
    lbl_8064DC20 = size;
    lbl_8064DC24 = (u8*)lbl_8064DC2C + 0x20;
    lbl_8064DC0C = size;
    lbl_8064DC2C->magic = 0xBAADF00D;
}
