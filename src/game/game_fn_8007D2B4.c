typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Matrix {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
} Matrix;

extern void *lbl_8064C4E4;
extern Vec3 lbl_8031CB20[];
extern u32 lbl_8031CB80[];

extern void *fn_8011FE34(void *);
extern void PSMTXQuat(Matrix *, void *);
extern void PSMTXMultVec(Matrix *, Vec3 *, Vec3 *);

void fn_8007D2B4(Vec3 *position, float x, float y, float z, int index, u8 alpha)
{
    Matrix matrix;
    Vec3 offset;
    void *transform;

    transform = fn_8011FE34(lbl_8064C4E4);
    PSMTXQuat(&matrix, transform);
    offset.x = x;
    offset.y = y;
    offset.z = z;
    PSMTXMultVec(&matrix, &offset, &offset);

    lbl_8031CB20[index].x = position->x + offset.x;
    lbl_8031CB20[index].y = position->y + offset.y;
    lbl_8031CB20[index].z = position->z + offset.z;
    lbl_8031CB80[index] = 0xFFFFFF00 | alpha;
}
