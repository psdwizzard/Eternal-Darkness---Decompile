typedef unsigned short u16;

extern volatile u16 *__peReg;

void GXPokeAlphaRead(int mode)
{
    __peReg[4] = (mode & ~4U) | 4U;
}
