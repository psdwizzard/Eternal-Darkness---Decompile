typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801C458C(u8 index, u8 mode, u32 value);

void fn_801CCFC0(u8 index, u8 mode, u32 value)
{
    fn_801C458C(index, mode, value);
}
