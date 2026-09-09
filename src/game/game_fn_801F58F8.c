typedef unsigned short u16;
typedef unsigned int u32;

extern char lbl_802FC688[];
extern void* lbl_8064D790;
extern void* lbl_8064D78C;
extern u16 lbl_8064D788;

extern void* fn_801FEA8C(u32, int, char*, int);
extern void fn_801F5980(void);

void fn_801F58F8(u32 value)
{
    u16 count = value;

    lbl_8064D790 = fn_801FEA8C(count * 12, 1, lbl_802FC688, 0x4E);
    lbl_8064D78C = fn_801FEA8C(count * 2, 1, lbl_802FC688, 0x4F);
    if (lbl_8064D790 != 0 && lbl_8064D78C != 0) {
        lbl_8064D788 = value;
        fn_801F5980();
    }
}
