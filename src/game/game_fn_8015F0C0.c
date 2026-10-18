int invertjump(int value)
{
    switch (value) {
    case 32:
        return 33;
    case 33:
        return 32;
    case 34:
        return 37;
    case 35:
        return 36;
    case 36:
        return 35;
    case 37:
        return 34;
    case 38:
    case 40:
        return 39;
    case 39:
    case 41:
        return 38;
    default:
        return 0;
    }
}
