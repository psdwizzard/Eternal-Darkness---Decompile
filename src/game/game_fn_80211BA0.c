typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);
extern void PSVECNormalize(Vec3 *, Vec3 *);
extern float PSVECDotProduct(Vec3 *, Vec3 *);

extern float lbl_80651628;

void C_VECHalfAngle(Vec3 *a, Vec3 *b, Vec3 *out) {
    Vec3 negA;
    Vec3 negB;
    Vec3 sum;

    negA.x = -a->x;
    negA.y = -a->y;
    negA.z = -a->z;
    negB.x = -b->x;
    negB.y = -b->y;
    negB.z = -b->z;
    PSVECNormalize(&negA, &negA);
    PSVECNormalize(&negB, &negB);
    PSVECAdd(&negA, &negB, &sum);
    if (PSVECDotProduct(&sum, &sum) > lbl_80651628) {
        PSVECNormalize(&sum, out);
    } else {
        *out = sum;
    }
}
