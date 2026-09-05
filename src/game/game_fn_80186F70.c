typedef signed short s16;

#pragma use_lmw_stmw on

extern int fn_800FBFB0(void);

void fn_80186F70(s16* output, int count, float step, float base, int range)
{
    s16* destination;
    int step_integer = (int)step;
    int sign = step_integer >> 31;
    int index;

    if (((sign ^ step_integer) - sign) > range) {
        int random_index;

        destination = output;
        random_index = 0;
        while (random_index < count) {
            int value = fn_800FBFB0() % step_integer;
            if (step_integer < 0) {
                value = -value;
            }
            *destination = (s16)(base + (float)value);
            base += step;
            random_index++;
            destination++;
        }
    } else {
        destination = output;
        index = 0;
        while (index < count) {
            int value = fn_800FBFB0() % range;
            if ((value & 1) != 0) {
                value = -value;
            }
            *destination = (s16)(base + (float)value);
            base += step;
            index++;
            destination++;
        }
    }
}
