typedef unsigned int u32;

int fn_801E779C(u32 value, int requested)
{
    int index;
    int found;

    found = -1;
    index = 0;
    while (index < 32) {
        if (value & (1 << index)) {
            found++;
            if (found == requested) {
                return index;
            }
        }
        index++;
    }
    return -1;
}
