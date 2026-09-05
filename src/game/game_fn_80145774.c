typedef unsigned short u16;

void fn_80145774(u16* values, int level, int threshold, int increment, int node)
{
    register int working = increment;
    int cursor = node + level;

    while (cursor != 0) {
        values[cursor] += working;
        cursor >>= 1;
    }
    if (values[1] < threshold)
        return;
    {
        working = level * 2;
        node = working - 1;
        for (; node >= level; node--) {
            if (values[node] > 1)
                values[node] >>= 1;
        }
        level--;
        {
            u16* child = working - 2 + values;
            u16* parent = values + level;
            for (; level != 0; level--) {
                *parent = child[0] + child[1];
                child -= 2;
                parent--;
            }
        }
    }
}
