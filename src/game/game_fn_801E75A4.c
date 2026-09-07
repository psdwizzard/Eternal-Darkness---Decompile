typedef unsigned int u32;

int fn_801E75A4(u32 value, int requested)
{
    int index;
    int found;

    found = 0;
    index = 0;

    while (index < 32) {
        if (value & 1) {
            if (found == requested) {
                return index;
            }
            found++;
        }
        value >>= 1;
        index++;
    }
    return -1;
}
