extern unsigned char __ctype_map[];

int iscntrl(int c)
{
    return __ctype_map[(unsigned char)c] & 3;
}
