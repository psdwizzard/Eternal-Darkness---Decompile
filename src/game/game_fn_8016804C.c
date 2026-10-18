extern void LoadBlock(void*, void*, unsigned int, void*, int);

double LoadNumber(void* object, void* input, int reverse)
{
    double value;
    LoadBlock(object, &value, sizeof(value), input, reverse);
    return value;
}
