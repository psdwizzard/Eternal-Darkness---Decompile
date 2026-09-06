typedef unsigned char u8;
typedef unsigned int u32;

extern u8 lbl_80619C20[];
extern u32 lbl_8061A494[];
extern u32 lbl_8061A4D4[];
extern u8 lbl_8064D3BC;
extern u8 lbl_8064D3AC;
extern u8* lbl_8064D3D0;
extern u32 fn_801CC6DC(int);
extern void fn_801CCF94(int);
extern void fn_801C21E8(u32);
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern void fn_801CCFE0(int);

void fn_801B9220(int arg0)
{
    int offset;
    u32 i;

    for (i = 0, offset = 0; i < lbl_80619C20[0x210]; offset += 0x404, i++) {
        u8* entry = lbl_8064D3D0 + offset;
        if ((u8)arg0 == entry[0x11F]) {
            if (*(u32*)(entry + 0xF4) != (u32)-1) {
                fn_801C21E8(*(u32*)(*(u8**)(entry + 0xF8) + 8));
            } else if (fn_801CC6DC(i)) {
                fn_801CCF94(i);
            }
        }
    }

    fn_801CE2B8();
    {
        u32 word_offset;
        u8 index = (u8)arg0;
        word_offset = (u32)index * 4;
        *(u32*)((u8*)lbl_8061A494 + word_offset) = 0;
        *(u32*)((u8*)lbl_8061A4D4 + word_offset) = 0;
        (&lbl_8064D3BC)[index] = 0xFF;
        (&lbl_8064D3AC)[index] = 0xFF;
    }
    fn_801CE280();
    fn_801CCFE0(arg0);
}
