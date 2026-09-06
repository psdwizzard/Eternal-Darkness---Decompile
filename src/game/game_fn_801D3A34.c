typedef signed short s16;

extern int fn_801D38E8(int);

s16 fn_801D3A34(int value, int base)
{
    int offset;
    offset = fn_801D38E8(value) - 1;
    return base + offset;
}
