extern unsigned char lbl_8063BF28[];

extern void GXSetProjection(void*, int);
extern void fn_801ED468(int);
extern void fn_801ECC4C(void);

void fn_801F03B8(void)
{
    GXSetProjection(lbl_8063BF28, 0);
    fn_801ED468(60);
    fn_801ECC4C();
}
