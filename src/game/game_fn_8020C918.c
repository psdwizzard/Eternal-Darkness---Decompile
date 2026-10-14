typedef unsigned short u16;
typedef unsigned int u32;

extern u16 lbl_8064C3E0;

/* Return the cached font encoding, initializing it from the video settings. */
u16 fn_8020C918(void)
{
    if (lbl_8064C3E0 <= 1U) {
        return lbl_8064C3E0;
    }

    switch (*(u32*)0x800000CC) {
    case 0:
        lbl_8064C3E0 = (*(volatile u16*)0xCC00206E & 2) ? 1 : 0;
        break;
    case 1:
    case 2:
    default:
        lbl_8064C3E0 = 0;
        break;
    }
    return lbl_8064C3E0;
}
