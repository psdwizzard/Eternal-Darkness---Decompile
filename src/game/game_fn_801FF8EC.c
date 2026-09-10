typedef unsigned int u32;

extern void* lbl_8064D858;
extern unsigned char lbl_8063F048[0x1400];
extern unsigned char lbl_8063F020[0x28];
extern u32 lbl_8064D7D8;

extern void* memset(void* destination, int value, u32 size);
extern void fn_801FEB54(int frame, int effects, int particles, int trails,
                        int textures, int anims);

void fn_801FF8EC(int effects, int particles, int trails, int textures, int anims)
{
    memset(lbl_8064D858, 0, 0x10C8E0);
    memset(lbl_8063F048, 0, 0x1400);
    memset(lbl_8063F020, 0, 0x28);
    lbl_8064D7D8 = 0;
    fn_801FEB54(0, effects, particles, trails, textures, anims);
    fn_801FEB54(1, effects, particles, trails, textures, anims);
}
