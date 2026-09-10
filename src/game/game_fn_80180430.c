typedef unsigned char u8;
typedef unsigned int u32;

u32 fn_80180430(u32* bits, u8 index)
{
    int byte_index;
    int bit_index;

    byte_index = index;
    bit_index = byte_index;
    bit_index -= byte_index & 0xE0;
    return (1U << bit_index) & bits[byte_index >> 5];
}
