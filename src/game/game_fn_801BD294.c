typedef unsigned short u16;
typedef unsigned int u32;

extern u16 lbl_8064D3F0;
extern u16 lbl_8064D3F2;
extern u16 lbl_8064D3F4;
extern u16 lbl_8064D3F6;
extern u16 lbl_8064D3F8;
extern u16 lbl_8064D3FA;
typedef struct Bucket {
    u16 count;
    u16 start;
} Bucket;

extern Bucket lbl_80622148[];
extern void fn_801CD284(u32 base, u32 length);

void fn_801BD294(u32 base, u32 length)
{
    long i;

    lbl_8064D3F0 = 0;
    lbl_8064D3F2 = 0;
    lbl_8064D3F4 = 0;
    lbl_8064D3F6 = 0;
    lbl_8064D3FA = 0;
    lbl_8064D3F8 = 0;
    for (i = 0; i < 512; ++i) {
        lbl_80622148[i].count = 0;
        lbl_80622148[i].start = 0;
    }
    fn_801CD284(base, length);
}
