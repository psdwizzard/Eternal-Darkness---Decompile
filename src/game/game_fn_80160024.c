int pushpc(int* const values, int value, int index, int count)
{
    for (; count != 0; count--)
        values[index++] = value - 1;
    return index;
}
