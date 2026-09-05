typedef signed short s16;
typedef signed long s32;

void fn_801A8CCC(s32 upper, s32 lower, s16* value, s16* delta)
{
    s32 current = *value;
    s32 step = *delta;

    if (step > 0) {
        if (current + step < upper) {
            current += step;
            *value = current;
        } else {
            *value = upper;
            *delta = -*delta;
        }
    } else if (step < 0) {
        if (current + step > lower) {
            current += step;
            *value = current;
        } else {
            *value = lower;
            *delta = -*delta;
        }
    }
}
