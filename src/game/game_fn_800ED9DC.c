typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_8064CBE8;
extern u32 lbl_8064CBF8;
extern u32 lbl_8064CBFC;
extern void *lbl_8064CC00[2];
extern void *lbl_8064CC0C[2];
extern unsigned char lbl_803281C0[];

extern void fn_800EEC44(void *, void *, u32, u32);
extern void DCStoreRange(void *, u32);
extern void GXInitTexObj(void *, void *, u16, u16, u32, u32, u32, u32);

void fn_800ED9DC(void *context, void *buffer)
{
    lbl_8064CC0C[lbl_8064CBE8] = buffer;
    fn_800EEC44(context, lbl_8064CC00[lbl_8064CBE8], lbl_8064CBFC,
                lbl_8064CBF8);
    DCStoreRange(lbl_8064CC00[lbl_8064CBE8],
                lbl_8064CBFC * lbl_8064CBF8 * 4);
    GXInitTexObj(lbl_803281C0, lbl_8064CC00[lbl_8064CBE8],
                (u16)lbl_8064CBFC, (u16)lbl_8064CBF8, 6, 0, 0, 0);
    lbl_8064CBE8 = lbl_8064CBE8 ^ 1;
}
