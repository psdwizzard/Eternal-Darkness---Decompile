unsigned long long fn_800F6218(unsigned int hi, unsigned int lo, unsigned int shift)
{
    unsigned int out_lo;
    unsigned int out_hi;
    int under = 32 - shift;
    int over = shift - 32;
    out_lo = lo >> shift;
    out_lo |= hi << under;
    out_lo |= hi >> over;
    out_hi = hi >> shift;
    return ((unsigned long long)out_hi << 32) | out_lo;
}
