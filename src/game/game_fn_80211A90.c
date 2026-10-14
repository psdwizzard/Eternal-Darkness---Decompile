typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Scale a vector; source and destination may be the same vector. */
void fn_80211A90(register const Vec3 *source, register Vec3 *destination,
                 register float scale)
{
    register float xy, z;

    /* ASM: psq_l loads the x/y pair and z into paired-single registers;
     * scalar C cannot represent the two independent lanes of the pair. */
    asm {
        psq_l xy, 0(source), 0, 0
        psq_l z, 8(source), 1, 0
    }
    /* ASM: ps_muls0 scales both lanes and psq_st stores the x/y pair.
     * C has no paired-single arithmetic or two-lane store operator. */
    asm {
        ps_muls0 xy, xy, scale
        psq_st xy, 0(destination), 0, 0
    }
    xy = z * scale;
    /* ASM: psq_st uses the paired-single quantized store path for z;
     * a scalar C assignment selects stfs instead. */
    asm { psq_st xy, 8(destination), 1, 0 }
}
