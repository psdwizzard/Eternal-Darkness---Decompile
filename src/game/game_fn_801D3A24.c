typedef signed short s16;

#pragma opt_propagation off
s16 fn_801D3A24(int value, int base)
{
    int offset;
    offset = value - 1;
    return base + offset;
}
#pragma opt_propagation reset
