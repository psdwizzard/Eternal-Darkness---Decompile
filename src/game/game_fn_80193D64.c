typedef signed short s16;

extern int rand(void);

void fn_80193D64(s16* output, int count, int step, int base, int range)
{
    int stride;
    int length;
    int modulus;
    s16* current;
    int positive;
    int value;
    int i;
    int random;

    stride = step;
    positive = stride > 0;
    length = count;
    if (range <= 0) {
        range = 1;
    }
    if (range > (stride < 0 ? -stride : stride)) {
        modulus = range;
    } else {
        modulus = stride < 0 ? -stride : stride;
    }
    value = base;
    current = output;
    i = 0;
    while (i < length) {
        random = rand() % modulus + 2;
        if (positive != 0) {
            random = -random;
        }
        *current = value + random;
        value += stride;
        current++;
        i++;
    }
}
