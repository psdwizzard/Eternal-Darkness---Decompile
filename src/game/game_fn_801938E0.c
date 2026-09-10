typedef signed char s8;
typedef unsigned short u16;

void fn_801938E0(void* object, s8 value)
{
    u16* field = (u16*)((unsigned char*)object + 0x9C);
    u16 current = *field;
    *field = (current & ~7) + value - 1;
}
