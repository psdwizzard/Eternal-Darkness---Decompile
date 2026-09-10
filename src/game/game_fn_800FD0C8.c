typedef unsigned long size_t;
typedef unsigned char char_map[32];

#define set_char_map(map, ch) ((map)[((ch) & 0xff) >> 3] |= (1 << ((ch) & 7)))
#define tst_char_map(map, ch) ((map)[((ch) & 0xff) >> 3] & (1 << ((ch) & 7)))

size_t fn_800FD0C8(const char* str, const char* set)
{
    const unsigned char* p;
    int c;
    char_map map = {0};

    p = (unsigned char*)set - 1;

    while (c = *++p)
        set_char_map(map, c);

    p = (unsigned char*)str - 1;

    while (c = *++p)
        if (tst_char_map(map, c))
            break;

    return (p - (unsigned char*)str);
}
