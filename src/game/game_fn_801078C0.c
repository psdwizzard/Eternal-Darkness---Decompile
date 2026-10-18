extern void HVQM4DecodeBpic(void*, void*, int, int, int);

void HVQM4DecodePpic(void* context, void* input, int value, int size)
{
    HVQM4DecodeBpic(context, input, value, size, value);
}
