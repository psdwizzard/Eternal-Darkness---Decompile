typedef unsigned short u16;

void fn_801FFCE4(u16 value)
{
    *(volatile u16*)0xCC008000 = value;
}
