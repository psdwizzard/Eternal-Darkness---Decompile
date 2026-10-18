typedef unsigned char u8;

extern unsigned char lbl_80606AE0[];
extern void* lbl_8064D24C;

extern void fn_801ED468(int);
extern int fn_8017FFB8(void);
extern int fn_8017FFB0(void);
extern int fn_8017FF98(void);
extern void GXSetArray(int, void*, u8);
extern void fn_801ECEC8(int, int, int);
extern void GXCallDisplayList(void*, void*);

void fn_801887C4(void* first, void* second, void* third)
{
    fn_801ED468(0x3C);
    GXSetArray(9, first, (u8)fn_8017FFB8());
    GXSetArray(0xB, third, (u8)fn_8017FF98());
    GXSetArray(0xD, second, (u8)fn_8017FFB0());
    fn_801ECEC8(1, 3, 0);
    GXCallDisplayList(lbl_80606AE0, lbl_8064D24C);
}
