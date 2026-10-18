extern unsigned char __ctype_map[];

int isdigit(int c)
{
    return __ctype_map[(unsigned char)c] & 0x10;
}
