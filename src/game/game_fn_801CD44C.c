typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xEC];
    u8 active;
    u8 padED[7];
} Entry;

extern Entry* lbl_8064D4AC;

u32 fn_801CD44C(u32 index)
{
    return lbl_8064D4AC[index].active == 1;
}
