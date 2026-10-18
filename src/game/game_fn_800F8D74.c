extern unsigned char __ctype_map[];

int isalnum(int c)
{
    return __ctype_map[(unsigned char)c] & 0xD0;
}
