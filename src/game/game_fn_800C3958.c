typedef unsigned char u8;

extern u8 lbl_80248730[];

unsigned int fn_800C3958(void *unused, unsigned int value)
{
    u8 *entry = lbl_80248730;
    int i;
    value &= 0xff;

    if (value == *entry) return value;
    #pragma unroll 7
    for (i = 0; i < 7; i++) {
        if (value == *++entry) return value;
    }
    if (value == entry[1]) return value;
    return value;
}
