typedef signed short s16;

#pragma use_lmw_stmw on

extern int rand(void);

void fn_80186D74(s16* output, int count, int low, int high, int offset)
{
    int upper;
    s16* destination;
    int step;
    int current;
    int index;

    upper = offset + low;
    if (high > low) {
        upper = offset + high;
    }
    step = (2 * upper - low - high) / count;
    current = low;
    destination = output;
    index = 0;
    while (index < count) {
        int value = rand() % step;
        if (step < 0) {
            value = -value;
        }
        *destination = current + value;
        current += step;
        if (current > upper) {
            step = -step;
        }
        destination++;
        index++;
    }
}
