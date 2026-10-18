/* Arithmetic right shift of the high/low word pair.
 * NonMatching: GC/1.3 separates the over-count subtraction and comparison.
 * See assignment 0c5c7f7d-6177-4b7c-9c11-19ee9d2d3538 for codegen evidence.
 */
long long __shr2i(int hi, unsigned int lo, unsigned int shift)
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
