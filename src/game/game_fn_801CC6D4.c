typedef unsigned char u8;

extern u8 salTimeOffset;

u8 hwGetTimeOffset(void)
{
    return salTimeOffset;
}
