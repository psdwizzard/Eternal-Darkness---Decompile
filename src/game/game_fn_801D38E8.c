int fn_801D38E8(int value)
{
    switch (value & 0xF) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 8:
        return 4;
    default:
        return 0;
    }
}
