extern unsigned int rand(void);

unsigned short fn_800E4A50(void)
{
    unsigned short value = rand() & 15;

    if (value == 0)
        value = 2;
    else if (value & 1)
        value++;
    if (value > 12 && (rand() & 1))
        value = 12;
    return value;
}
