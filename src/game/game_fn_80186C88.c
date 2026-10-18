typedef signed short s16;

#pragma use_lmw_stmw on

extern int rand(void);

void fn_80186C88(s16* output, int count, int step, int base, int magnitude)
{
    int sign = step >> 31;

    if (((sign ^ step) - sign) > magnitude) {
        s16* destination;
        int index;
        int current;

        current = base;
        destination = output;
        index = 0;
        while (index < count) {
            int value = rand() % step + 1;
            if (step < 0) {
                value = -value;
            }
            *destination = current + value;
            current += step;
            destination++;
            index++;
        }
    } else {
        int index;
        int current;
        s16* destination;

        if (magnitude <= 0) {
            magnitude = 1;
        }
        current = base;
        destination = output;
        index = 0;
        while (index < count) {
            int value = rand() % magnitude + 2;
            if ((value & 1) != 0) {
                value = -value;
            }
            *destination = current + value;
            current += step;
            destination++;
            index++;
        }
    }
}
