typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Matrix34 {
    float m[3][4];
} Matrix34;

extern void PSVECNormalize(Vec3* in, Vec3* out);
extern void PSVECCrossProduct(Vec3* a, Vec3* b, Vec3* out);

/* Build a look-at view matrix from eye, up and target. */
void C_MTXLookAt(Matrix34* mtx, Vec3* eye, Vec3* up, Vec3* target) {
    Vec3 look;
    Vec3 right;
    Vec3 camUp;
    float x, y, z;

    look.x = eye->x - target->x;
    look.y = eye->y - target->y;
    look.z = eye->z - target->z;
    PSVECNormalize(&look, &look);
    PSVECCrossProduct(up, &look, &right);
    PSVECNormalize(&right, &right);
    PSVECCrossProduct(&look, &right, &camUp);

    mtx->m[0][0] = right.x;
    mtx->m[0][1] = right.y;
    mtx->m[0][2] = right.z;
    x = eye->x * right.x;
    y = eye->y * right.y;
    z = eye->z * right.z;
    mtx->m[0][3] = -(z + (x + y));
    mtx->m[1][0] = camUp.x;
    mtx->m[1][1] = camUp.y;
    mtx->m[1][2] = camUp.z;
    x = eye->x * camUp.x;
    y = eye->y * camUp.y;
    z = eye->z * camUp.z;
    mtx->m[1][3] = -(z + (x + y));
    mtx->m[2][0] = look.x;
    mtx->m[2][1] = look.y;
    mtx->m[2][2] = look.z;
    x = eye->x * look.x;
    y = eye->y * look.y;
    z = eye->z * look.z;
    mtx->m[2][3] = -(z + (x + y));
}
