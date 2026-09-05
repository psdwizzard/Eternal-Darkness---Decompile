#pragma global_optimizer off
unsigned int fn_80178F14(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int low;
    int high;
    int x = x2 - x1;
    int y = y2 - y1;
    int z = z2 - z1;

    x = x < 0 ? -x : x;
    y = y < 0 ? -y : y;
    z = z < 0 ? -z : z;

    if (x < y) {
        low = x;
        high = y;
    } else {
        low = y;
        high = x;
    }

    if (z < high) {
        y = high;
        high = z;
    } else {
        y = z;
    }

    return y + ((low + high) >> 2);
}
#pragma global_optimizer reset
