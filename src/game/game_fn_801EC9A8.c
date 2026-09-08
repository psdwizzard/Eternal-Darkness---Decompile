typedef unsigned char u8;
typedef unsigned int u32;

extern int lbl_8064D67C;
extern int lbl_8064C5D4;
extern u8 lbl_8063B3DC[80];
extern void* memset(void*, int, u32);

void fn_801EC9A8(void)
{
    lbl_8064D67C = 0;
    lbl_8064C5D4 = 0;
    memset(lbl_8063B3DC, 0, 80);
}
