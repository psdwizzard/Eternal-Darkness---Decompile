/* Reset the debug heap to its initial free region. */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct HeapHeader {
    u8 pad00[0x18];
    u32 magic;
    u8 pad1C[0x4];
} HeapHeader;

extern u32 lbl_8064DC20;
extern u8* lbl_8064DC24;
extern u32 lbl_8064DC28;
extern HeapHeader* lbl_8064DC2C;

void fn_8022F75C(void) {
    lbl_8064DC24 = (u8*)lbl_8064DC2C + 0x20;
    lbl_8064DC20 = lbl_8064DC28;
    lbl_8064DC2C->magic = 0xBAADF00D;
}
