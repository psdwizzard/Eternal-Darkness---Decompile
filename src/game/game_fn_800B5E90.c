extern void fn_800B2548(int, int);

void fn_800B5E90(int value, int status)
{
    switch (status) {
    case -6:
        fn_800B2548(8, value);
        break;
    case -13:
        fn_800B2548(9, value);
        break;
    case -2:
        fn_800B2548(43, value);
        break;
    case -3:
    case -1:
        fn_800B2548(42, value);
        break;
    case 0:
        break;
    default:
        fn_800B2548(41, value);
        break;
    }
}
