extern int fn_801290D0(void *);
extern void fn_801296F8(void *, int);

int fn_800D386C(void *state, int value)
{
    register unsigned long value_r = (unsigned long)value;

    int result = 0;

    if ((fn_801290D0(state) & 1) != 0) {
        fn_801296F8(state, value_r);
        result = 1;
    }
    return result;
}
