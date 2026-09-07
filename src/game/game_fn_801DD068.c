typedef unsigned char u8;

int fn_801DD068(int value, int unused, u8 kind)
{
    switch (kind) {
    case 1:
        return 900;
    case 2:
        return 1200;
    case 3:
        return 1800;
    default:
        return value;
    }
}
