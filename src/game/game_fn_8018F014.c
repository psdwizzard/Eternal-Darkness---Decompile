typedef signed short s16;
typedef unsigned short u16;

extern int rand(void);

void fn_8018F014(s16* values, u16 range)
{
    int mask = range * 2 - 1;

    values[0] += range - (rand() & mask);
    values[1] += range - (rand() & mask);
    values[2] += range - (rand() & mask);
}
