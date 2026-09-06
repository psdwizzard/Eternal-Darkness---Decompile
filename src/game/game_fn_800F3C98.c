typedef unsigned char u8;

extern void fn_800F35AC(void *, unsigned int);

int fn_800F3C98(u8 options, unsigned int start, unsigned int end)
{
    if (start < end) {
        fn_800F35AC((void *)start, end - start);
        return 0;
    }
    return 0x700;
}
