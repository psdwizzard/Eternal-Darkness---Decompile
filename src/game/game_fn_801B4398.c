typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

u8* GetStreamValue(u8* input, u16* first, s16* second)
{
    u8 high = input[0];
    u8 low = input[1];

    if (high == 0x80 && low == 0)
        return 0;

    if (high & 0x80) {
        *first = ((high & 0x7F) << 8) | low;
        input += 2;
    } else {
        *first = high;
        input++;
    }

    high = input[0];
    low = input[1];
    if (high & 0x80) {
        s16 value = ((high & 0x7F) << 8) | low;
        value <<= 1;
        value >>= 1;
        *second = value;
        input += 2;
    } else {
        s16 value = high;
        value <<= 9;
        value >>= 9;
        *second = value;
        input++;
    }
    return input;
}
