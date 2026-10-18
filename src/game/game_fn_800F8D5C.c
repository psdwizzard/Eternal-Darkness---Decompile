extern unsigned char __ctype_map[];

int isalpha(int c)
{
    return __ctype_map[(unsigned char)c] & 0xC0;
}
