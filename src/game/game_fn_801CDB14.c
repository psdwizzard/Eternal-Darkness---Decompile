typedef unsigned int u32;

extern u32 aramWrite;

void aramRemoveData(void* unused, u32 size)
{
    aramWrite -= (size + 31) & ~31;
}
