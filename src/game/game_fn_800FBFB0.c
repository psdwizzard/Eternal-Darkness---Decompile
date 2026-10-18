extern unsigned int lbl_8064B848;

unsigned int rand(void)
{
    lbl_8064B848 = lbl_8064B848 * 1103515245 + 12345;
    return (lbl_8064B848 >> 16) & 0x7FFF;
}
