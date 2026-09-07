typedef unsigned int u32;

u32 fn_801E7578(u32 value)
{
    int bit;
    u32 count = 0;

    for (bit = 1; bit != 0; bit <<= 1) {
        if (value & bit) {
            count++;
        }
    }
    return count;
}
