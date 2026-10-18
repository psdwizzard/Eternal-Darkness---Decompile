/* memmove (0x800F9990, 204 bytes): MSL memmove. */

typedef unsigned long size_t;

void __copy_longs_rev_unaligned(void* dst, const void* src, size_t n); /* __copy_longs_rev_unaligned */
void __copy_longs_unaligned(void* dst, const void* src, size_t n); /* __copy_longs_unaligned */
void __copy_longs_rev_aligned(void* dst, const void* src, size_t n); /* __copy_longs_rev_aligned */
void __copy_longs_aligned(void* dst, const void* src, size_t n); /* __copy_longs_aligned */

void* memmove(void* dst, const void* src, size_t n) {
    const char* p;
    char* q;
    int rev = ((unsigned long)src < (unsigned long)dst);

    if (n >= 32) {
        if (((unsigned long)dst ^ (unsigned long)src) & 3) {
            if (!rev)
                __copy_longs_unaligned(dst, src, n);
            else
                __copy_longs_rev_unaligned(dst, src, n);
        } else if (!rev) {
            __copy_longs_aligned(dst, src, n);
        } else {
            __copy_longs_rev_aligned(dst, src, n);
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
