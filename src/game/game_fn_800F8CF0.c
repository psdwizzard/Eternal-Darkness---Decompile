extern unsigned char __lower_map[];

int tolower(int c)
{
    if (c == -1) {
        return -1;
    }
    return __lower_map[(unsigned char)c];
}
