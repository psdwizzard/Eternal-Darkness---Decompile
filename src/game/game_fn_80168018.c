extern void LoadBlock(void*, void*, unsigned int, void*, int);

unsigned int LoadSize(void* object, void* input, int reverse)
{
    unsigned int value;
    LoadBlock(object, &value, sizeof(value), input, reverse);
    return value;
}
