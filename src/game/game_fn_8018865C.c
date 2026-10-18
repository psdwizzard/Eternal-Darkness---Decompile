typedef unsigned char u8;

extern unsigned char lbl_80606780[];
extern void* lbl_8064D250;

extern void fn_801ED468(int);
extern int fn_8017FFB8(void);
extern int fn_8017FFB0(void);
extern int fn_8017FF98(void);
extern void GXSetArray(int, void*, u8);
extern void fn_801ECF50(int);
extern void fn_801ECEC8(int, int, int);
extern void GXCallDisplayList(void*, void*);
extern void GXSetCoPlanar(int);

void fn_8018865C(void* first, void* second, void* third)
{
    fn_801ED468(0x3C);
    GXSetArray(9, first, (u8)fn_8017FFB8());
    GXSetArray(0xD, second, (u8)fn_8017FFB0());
    GXSetArray(0xB, third, (u8)fn_8017FF98());
    fn_801ECF50(3);
    fn_801ECEC8(1, 3, 0);
    GXCallDisplayList(lbl_80606780, lbl_8064D250);
    GXSetCoPlanar(0);
}
