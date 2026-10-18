extern void LoadBlock(void*, void*, unsigned int, void*, int);

int LoadInt(void* object, void* input, int reverse)
{
    int value;
    LoadBlock(object, &value, sizeof(value), input, reverse);
    return value;
}
