/* MSL __copy_longs_rev_unaligned: reverse copy for differing word alignment.
 * MWCC permits cast lvalues to walk the pointers through byte and word views. */
#define cps ((const unsigned char*)src)
#define cpd ((unsigned char*)dst)
#define lps ((const unsigned long*)src)
#define lpd ((unsigned long*)dst)

void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n)
{
    unsigned long i, v1, v2;
    unsigned int src_offset, left_shift, right_shift;

    cpd += n;
    cps += n;
    i = (unsigned long)dst & 3;
    if (i) {
        n -= i;
        do {
            *--cpd = *--cps;
        } while (--i);
    }

    src_offset = (unsigned int)src & 3;
    left_shift = src_offset << 3;
    right_shift = 32 - left_shift;
    cps += 4 - src_offset;
    i = n >> 3;
    v1 = *--lps;
    do {
        v2 = *--lps;
        *--lpd = (v2 << left_shift) | (v1 >> right_shift);
        v1 = *--lps;
        *--lpd = (v1 << left_shift) | (v2 >> right_shift);
    } while (--i);

    if (n & 4) {
        v2 = *--lps;
        *--lpd = (v2 << left_shift) | (v1 >> right_shift);
    }

    n &= 3;
    if (n) {
        cps += src_offset;
        do {
            *--cpd = *--cps;
        } while (--n);
    }
}
