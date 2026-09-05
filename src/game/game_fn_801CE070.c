typedef unsigned char u8;

extern u8 lbl_8064D534;
extern u8* lbl_8064D514;

void* fn_801CE070(void)
{
    return lbl_8064D514 + (u8)((lbl_8064D534 + 2) % 4) * 0x280;
}
