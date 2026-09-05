typedef unsigned char u8;

int fn_8019CE08(u8* object, u8 index, int mask)
{
    u8 value;
    value = object[index + 0xAC];
    return value & mask;
}
