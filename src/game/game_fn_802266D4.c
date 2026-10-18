typedef unsigned char u8;
typedef unsigned short u16;

extern volatile u16 *__peReg;

void GXPokeAlphaMode(int compare, u8 threshold)
{
    __peReg[3] = (compare << 8) | threshold;
}
