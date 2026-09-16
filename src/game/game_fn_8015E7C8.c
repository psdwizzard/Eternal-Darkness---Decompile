typedef unsigned int u32;

typedef struct StreamEntry {
    unsigned char pad0[0x10];
    u32 start;
    u32 size;
} StreamEntry;

extern int lbl_8064D178;
extern u32 lbl_8064D1B4;
extern StreamEntry lbl_805B6F80[];

u32 fn_8015E7C8(u32 size)
{
    u32 position = lbl_8064D1B4;
    u32 end = lbl_805B6F80[lbl_8064D178].start +
              lbl_805B6F80[lbl_8064D178].size;
    u32 result = position;

    if (position + size >= end)
        result = 0;
    if ((u32)(position + size >= end) <= 0)
        lbl_8064D1B4 += size;
    return result;
}
