typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

asm float fn_8013C418(const Vec3* origin, const Vec3* point,
                      const Vec3* direction, Vec3* output)
{
    nofralloc
    psq_l f3, 4(r4), 0, 0
    psq_l f6, 4(r3), 0, 0
    ps_sub f6, f6, f3
    psq_l f5, 4(r5), 0, 0
    ps_mul f6, f6, f5
    psq_l f2, 0(r4), 0, 0
    psq_l f1, 0(r3), 0, 0
    ps_sub f1, f1, f2
    psq_l f4, 0(r5), 0, 0
    ps_madd f1, f1, f4, f6
    ps_sum0 f1, f1, f6, f6
    ps_merge00 f1, f1, f1
    ps_madd f6, f1, f4, f2
    psq_st f6, 0(r6), 0, 0
    ps_madd f6, f1, f5, f3
    ps_merge10 f6, f6, f6
    psq_st f6, 8(r6), 1, 0
    blr
}
