typedef unsigned int u32;
typedef unsigned char u8;

typedef struct HeapEntry HeapEntry;
struct HeapEntry {
    HeapEntry* next;
    u32 value;
    u32 size;
    u32 allocation_size;
};

typedef struct HeapStorage {
    u8 pad[0x508];
    HeapEntry entries[64];
} HeapStorage;

extern HeapStorage lbl_80630A30;
extern HeapEntry* lbl_8064D500;
extern HeapEntry* lbl_8064D504;
extern HeapEntry* lbl_8064D508;
extern u32 lbl_8064D4E8;
extern u32 lbl_8064D4F0;

void fn_801CDB2C(void)
{
    u8* base = (u8*)&lbl_80630A30;
    u32 i;

    lbl_8064D500 = 0;
    lbl_8064D504 = 0;
    lbl_8064D508 = (HeapEntry*)(base + 0x508);
    for (i = 1; i < 64; i++) {
        ((HeapEntry*)(base + 0x508))[i - 1].next =
            &((HeapEntry*)(base + 0x508))[i];
    }
    ((HeapEntry*)(base + 0x508))[i - 1].next = 0;
    lbl_8064D4F0 = lbl_8064D4E8;
}
