long long fn_800F623C(int hi, unsigned int lo, unsigned int shift)
{
    unsigned int out_lo;
    int shifted_hi;
    int under = 32 - shift;
    int over = shift - 32;
    out_lo = lo >> shift;
    out_lo |= hi << under;
    shifted_hi = hi >> over;
    if (over > 0) {
        out_lo |= shifted_hi;
    }
    return ((unsigned long long)(hi >> shift) << 32) | out_lo;
}
