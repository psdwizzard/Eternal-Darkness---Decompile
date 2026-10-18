extern unsigned char __ctype_map[];

int isspace(int c)
{
    return __ctype_map[(unsigned char)c] & 6;
}
