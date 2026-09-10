unsigned long long fn_800F61F4(unsigned int hi, unsigned int lo, unsigned int shift)
{
    unsigned int out_hi;
    unsigned int out_lo;
    int under = 32 - shift;
    int over = shift - 32;
    out_hi = hi << shift;
    out_hi |= lo >> under;
    out_hi |= lo << over;
    out_lo = lo << shift;
    return ((unsigned long long)out_hi << 32) | out_lo;
}
