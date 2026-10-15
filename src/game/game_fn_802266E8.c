typedef unsigned short u16;

extern volatile u16 *__peReg;

void fn_802266E8(int mode)
{
    __peReg[4] = (mode & ~4U) | 4U;
}
