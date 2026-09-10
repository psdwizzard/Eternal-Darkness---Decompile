typedef unsigned short u16;

void fn_801FFCF0(u16 value)
{
    *(volatile u16*)0xCC008000 = value;
}
