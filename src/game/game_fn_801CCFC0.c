typedef unsigned char u8;
typedef unsigned int u32;

extern void salActivateStudio(u8 index, u8 mode, u32 value);

void hwActivateStudio(u8 index, u8 mode, u32 value)
{
    salActivateStudio(index, mode, value);
}
