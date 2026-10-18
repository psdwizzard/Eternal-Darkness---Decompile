/* MSL __copy_longs_rev_aligned: reverse copy for equally aligned pointers.
 * MWCC permits cast lvalues to walk the pointers through byte and word views. */
#define cps ((const unsigned char*)src)
#define cpd ((unsigned char*)dst)
#define lps ((const unsigned long*)src)
#define lpd ((unsigned long*)dst)

void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n)
{
    unsigned long i;

    cpd += n;
    cps += n;
    i = (unsigned long)dst & 3;
    if (i) {
        n -= i;
        do {
            *--cpd = *--cps;
        } while (--i);
    }

    i = n >> 5;
    if (i) {
        do {
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
            *--lpd = *--lps;
        } while (--i);
    }

    i = (n >> 2) & 7;
    if (i) {
        do {
            *--lpd = *--lps;
        } while (--i);
    }

    n &= 3;
    if (n) {
        do {
            *--cpd = *--cps;
        } while (--n);
    }
}
