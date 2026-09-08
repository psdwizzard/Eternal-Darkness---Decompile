typedef unsigned char u8;

u8 fn_801EC304(u8* data, u8 x, u8 y)
{
    return data[x + (y << 8)];
}
