typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern float fn_80211B44(Vec3 *, Vec3 *);

extern float lbl_80651628;

void fn_80211BA0(Vec3 *a, Vec3 *b, Vec3 *out) {
    Vec3 negA;
    Vec3 negB;
    Vec3 sum;

    negA.x = -a->x;
    negA.y = -a->y;
    negA.z = -a->z;
    negB.x = -b->x;
    negB.y = -b->y;
    negB.z = -b->z;
    fn_80211AAC(&negA, &negA);
    fn_80211AAC(&negB, &negB);
    fn_80211A48(&negA, &negB, &sum);
    if (fn_80211B44(&sum, &sum) > lbl_80651628) {
        fn_80211AAC(&sum, out);
    } else {
        *out = sum;
    }
}
