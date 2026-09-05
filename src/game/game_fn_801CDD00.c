typedef unsigned int u32;
typedef unsigned char u8;

typedef struct HeapEntry HeapEntry;
struct HeapEntry {
    HeapEntry* next;
    u32 value;
    u32 size;
    u32 allocation_size;
};

extern HeapEntry lbl_80630F38[];

u32 fn_801CDD00(u8 index, u32* size)
{
    if (size != 0) {
        *size = lbl_80630F38[index].size;
    }
    return lbl_80630F38[index].value;
}
