/* MSL __copy_longs_aligned: forward copy for equally aligned pointers. */
#define cps ((const unsigned char*)src)
#define cpd ((unsigned char*)dst)
#define lps ((const unsigned long*)src)
#define lpd ((unsigned long*)dst)

void fn_800F9C7C(void* dst, const void* src, unsigned long n)
{
    unsigned long i;

    i = (-(unsigned long)dst) & 3;
    cps = (const unsigned char*)src - 1;
    cpd = (unsigned char*)dst - 1;
    if (i) {
        n -= i;
        do {
            *++cpd = *++cps;
        } while (--i);
    }

    lps = (const unsigned long*)(cps + 1) - 1;
    lpd = (unsigned long*)(cpd + 1) - 1;
    i = n >> 5;
    if (i) {
        do {
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
            *++lpd = *++lps;
        } while (--i);
    }

    i = (n >> 2) & 7;
    if (i) {
        do {
            *++lpd = *++lps;
        } while (--i);
    }

    cps = (const unsigned char*)(lps + 1) - 1;
    cpd = (unsigned char*)(lpd + 1) - 1;
    n &= 3;
    if (n) {
        do {
            *++cpd = *++cps;
        } while (--n);
    }
}
