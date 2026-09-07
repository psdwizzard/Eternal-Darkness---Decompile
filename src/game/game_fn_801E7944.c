typedef unsigned int u32;

extern void* memset(void* destination, int value, u32 size);

void fn_801E7944(u32* bits)
{
    memset(bits + 1, 0, bits[0] >> 2);
}
