typedef signed short s16;

extern int rand(void);

void fn_80193E1C(s16* output, int count, float step, int base, int range)
{
    float stride;
    int length;
    int modulus;
    s16* current;
    int positive;
    float value;
    int i;
    int random;

    stride = step;
    positive = stride < 0.0f;
    length = count;
    if (range <= 0) {
        range = 1;
    }
    random = (int)stride;
    modulus = ((random >> 31) ^ random) - (random >> 31);
    if (range > modulus) {
        modulus = range;
    }
    value = (float)base;
    current = output;
    i = 0;
    while (i < length) {
        random = rand() % modulus + 2;
        if (positive != 0) {
            random = -random;
        }
        *current = (s16)(value + (float)random);
        value += stride;
        current++;
        i++;
    }
}
