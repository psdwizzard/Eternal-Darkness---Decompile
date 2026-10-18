unsigned int luaO_power2(unsigned int value)
{
    unsigned int size = 4;

    while (size <= value) {
        size <<= 1;
    }
    return size;
}
