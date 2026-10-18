typedef signed short s16;
typedef unsigned short u16;

extern int rand(void);

void fn_8018EFB0(s16* values, u16 amount, int index)
{
    values[index] += amount - (rand() & ((amount << 1) - 1));
}
