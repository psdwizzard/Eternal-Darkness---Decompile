typedef unsigned int u32;

int fn_80047428(int value)
{
    if (value == 0 || value == 9 || value == 0x96 || value == 0x12 ||
        (u32)(value - 0x45) <= 1 || (u32)(value - 0x49) <= 3 ||
        value == 0x51 || value == 0x55 ||
        (u32)(value - 0x77) <= 2 || value == 0x7A) {
        return 1;
    }
    return 0;
}
