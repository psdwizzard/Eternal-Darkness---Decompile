long long fn_800F623C(int hi, unsigned int lo, unsigned int shift)
{
    unsigned int out_lo;
    int under = 32 - shift;
    int over = shift - 32;
    out_lo = lo >> shift;
    out_lo |= hi << under;
    if (over > 0) {
        out_lo |= hi >> over;
    }
    return ((unsigned long long)(hi >> shift) << 32) | out_lo;
}
