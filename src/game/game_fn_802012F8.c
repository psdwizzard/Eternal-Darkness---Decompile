extern unsigned char lbl_80640448[];
extern void *memset(void *, int, unsigned int);

void fn_802012F8(void)
{
    memset(lbl_80640448, 0, 0x640);
}
