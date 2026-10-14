/* fn_800F98EC: MSL memcmp. */

typedef unsigned long size_t;

int fn_800F98EC(const void *a, const void *b, size_t n) {
    const unsigned char *p = (const unsigned char *)a - 1;
    const unsigned char *q = (const unsigned char *)b - 1;

    for (n++; --n;) {
        if (*++p != *++q) {
            return (*p < *q) ? -1 : 1;
        }
    }
    return 0;
}
