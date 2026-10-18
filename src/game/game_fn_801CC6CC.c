typedef unsigned char u8;

extern u8 salTimeOffset;

void hwSetTimeOffset(u8 value)
{
    salTimeOffset = value;
}
