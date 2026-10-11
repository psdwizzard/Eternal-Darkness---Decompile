int fn_800AF0DC(int kind)
{
    switch ((unsigned int)kind) {
    case 3:
    case 7:
    case 10:
        return 23;
    case 0:
    case 5:
    case 9:
        return 22;
    case 2:
    case 6:
        return 27;
    default:
        return 22;
    }
}
