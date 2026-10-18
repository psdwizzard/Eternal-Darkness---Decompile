typedef signed short s16;

#pragma use_lmw_stmw on

extern int rand(void);

void fn_80186E10(s16* output, int count, int low, int high, int offset)
{
    int upper;
    float step;
    float current;
    s16* destination;
    int step_integer;
    int index;

    upper = offset + low;
    if (high > low) {
        upper = offset + high;
    }
    step = (float)(2 * upper - low - high) / (float)count;
    step_integer = (int)step;
    current = (float)low;
    destination = output;
    index = 0;
    while (index < count) {
        int value = rand() % step_integer;
        if (step < 0.0f) {
            value = -value;
        }
        *destination = (s16)(current + (float)value);
        current += step;
        if (current > (float)upper) {
            step = -step;
        }
        destination++;
        index++;
    }
}
