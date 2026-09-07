typedef unsigned int u32;

int fn_801E76E0(u32 value)
{
    int index;
    int result;

    result = -1;
    index = 0;
    while (index < 32) {
        if (value & 1) {
            result = index;
        }
        value >>= 1;
        index++;
    }
    return result;
}
