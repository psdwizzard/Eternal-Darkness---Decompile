int getunopr(int token)
{
    switch (token) {
    case 0x10C:
        return 1;
    case 0x2D:
        return 0;
    default:
        return 2;
    }
}
