void fn_801F3924(unsigned short x, unsigned short y, unsigned short z)
{
    *(volatile unsigned short*)0xCC008000 = x;
    *(volatile unsigned short*)0xCC008000 = y;
    *(volatile unsigned short*)0xCC008000 = z;
}
