typedef unsigned char u8;

typedef struct ArenaEntry {
    u8 pad00[0x50];
    u8 flag;
    u8 pad51[0x6B];
} ArenaEntry;

extern ArenaEntry lbl_80628CB0[];

void salDeactivateStudio(u8 index)
{
    lbl_80628CB0[index].flag = 0;
}
