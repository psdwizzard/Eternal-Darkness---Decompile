typedef unsigned char u8;
typedef unsigned int u32;

extern u32 lbl_80255800[];
extern u32 lbl_80255814[];
extern u8 lbl_802FC5BC[];

extern void fn_801939A8(u8* object, const u32* color, const u32* first,
                       const u32* second);

void fn_801D3CAC(int type, int use_alt_color, u8* object)
{
    const u32* color = 0;
    u32 first;
    u32 second;

    if (type == 4) {
        color = (u32*)lbl_802FC5BC;
    }
    first = lbl_80255800[type];
    if (use_alt_color != 0) {
        color = (u32*)(lbl_802FC5BC + 0xC);
    }
    second = lbl_80255814[type];
    fn_801939A8(object, color, &first, &second);
}
