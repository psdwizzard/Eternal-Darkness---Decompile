typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 bytes[0xF4];
} Entry;

extern Entry* lbl_8064D4AC;
extern void fn_801C7684(Entry* entry);

void fn_801CD068(u32 index)
{
    fn_801C7684(&lbl_8064D4AC[index]);
}
