typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern Vec3 lbl_8032808C[];
extern int lbl_8064CBD0;
extern void fn_800EC3C4(Vec3 *v);

void fn_800EC434(unsigned char depth, Vec3 *a, Vec3 *b, Vec3 *c)
{
    Vec3 ab;
    Vec3 bc;
    Vec3 ca;
    int nextDepth;

    if (depth == 0) {
        lbl_8032808C[lbl_8064CBD0++] = *a;
        lbl_8032808C[lbl_8064CBD0++] = *b;
        lbl_8032808C[lbl_8064CBD0++] = *c;
        return;
    }

    ab.x = a->x + b->x;
    bc.x = b->x + c->x;
    ca.x = c->x + a->x;
    ab.y = a->y + b->y;
    bc.y = b->y + c->y;
    ca.y = c->y + a->y;
    ab.z = a->z + b->z;
    bc.z = b->z + c->z;
    ca.z = c->z + a->z;

    fn_800EC3C4(&ab);
    fn_800EC3C4(&bc);
    fn_800EC3C4(&ca);
    nextDepth = depth - 1;
    fn_800EC434(nextDepth, a, &ab, &ca);
    fn_800EC434(nextDepth, b, &bc, &ab);
    fn_800EC434(nextDepth, c, &ca, &bc);
    fn_800EC434(nextDepth, &ab, &bc, &ca);
}
