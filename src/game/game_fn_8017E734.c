typedef signed short s16;

extern unsigned int rand(void);

void fn_8017E734(s16* output, s16* base, s16* change, s16* limit,
                 s16* accumulator)
{
    int i;

    for (i = 0; i < 3; i++) {
        accumulator[i] += change[i];
        output[i] = base[i] + accumulator[i];
        if (output[i] > base[i] + limit[i]) {
            output[i] = base[i] + limit[i];
            change[i] = -((rand() & 7) + 1);
        } else if (output[i] < base[i] - limit[i]) {
            output[i] = base[i] - limit[i];
            change[i] = (rand() & 7) + 1;
        }
    }
}
