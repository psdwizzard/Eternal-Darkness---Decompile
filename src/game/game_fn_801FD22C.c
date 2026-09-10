typedef short s16;

void fn_801FD22C(s16 x, s16 y, s16 z)
{
    *(volatile s16*)0xCC008000 = x;
    *(volatile s16*)0xCC008000 = y;
    *(volatile s16*)0xCC008000 = z;
}
