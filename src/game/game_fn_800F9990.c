/* fn_800F9990 (0x800F9990, 204 bytes): MSL memmove. */

typedef unsigned long size_t;

void fn_800F9A5C(void* dst, const void* src, size_t n); /* __copy_longs_rev_unaligned */
void fn_800F9B0C(void* dst, const void* src, size_t n); /* __copy_longs_unaligned */
void fn_800F9BD0(void* dst, const void* src, size_t n); /* __copy_longs_rev_aligned */
void fn_800F9C7C(void* dst, const void* src, size_t n); /* __copy_longs_aligned */

void* fn_800F9990(void* dst, const void* src, size_t n) {
    const char* p;
    char* q;
    int rev = ((unsigned long)src < (unsigned long)dst);

    if (n >= 32) {
        if (((unsigned long)dst ^ (unsigned long)src) & 3) {
            if (!rev)
                fn_800F9B0C(dst, src, n);
            else
                fn_800F9A5C(dst, src, n);
        } else if (!rev) {
            fn_800F9C7C(dst, src, n);
        } else {
            fn_800F9BD0(dst, src, n);
        }
        return dst;
    }

    if (!rev) {
        for (p = (const char*)src - 1, q = (char*)dst - 1, n++; --n;)
            *++q = *++p;
    } else {
        for (p = (const char*)src + n, q = (char*)dst + n, n++; --n;)
            *--q = *--p;
    }
    return dst;
}
