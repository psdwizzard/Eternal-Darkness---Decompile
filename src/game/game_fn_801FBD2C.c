typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Pair {
    int x;
    int y;
    int z;
} Pair;

typedef struct Matrix {
    float m[15];
} Matrix;

extern const float lbl_806514D8;
extern void fn_80211584(Matrix*, Vec3*, Vec3*, Vec3*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern void fn_80211AAC(Vec3*, Vec3*);
extern void fn_80211B64(Vec3*, Vec3*, Vec3*);
extern void fn_80211764(Matrix*, Vec3*, Vec3*, int);
extern void fn_801F6BD8(Vec3*, Pair*, int, int);

int fn_801FBD2C(Vec3* first, Vec3* second, Vec3* third, Vec3* fourth,
                float margin)
{
    Matrix matrix;
    Vec3 source[4];
    Vec3 corners[4];
    Vec3 scaled;
    Vec3 axis;
    Pair projected;
    int i;
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    fn_80211584(&matrix, first, third, second);
    fn_80211A6C(first, second, &axis);
    fn_80211B64(&axis, third, &scaled);
    fn_80211AAC(&scaled, &scaled);
    scaled.x *= lbl_806514D8;
    scaled.y *= lbl_806514D8;
    scaled.z *= lbl_806514D8;
    fn_80211A6C(fourth, &scaled, &source[0]);
    fn_80211A48(fourth, &scaled, &source[1]);
    source[2] = source[1];
    source[3] = source[0];
    source[2].z += margin;
    source[3].z += margin;
    fn_80211764(&matrix, source, corners, 4);
    fn_801F6BD8(corners, &projected, 1, 0);
    min_x = projected.x;
    max_x = projected.x;
    min_y = projected.y;
    max_y = projected.y;
    for (i = 1; i < 4; i++) {
        fn_801F6BD8(&corners[i], &projected, 1, 0);
        if (min_x > projected.x)
            min_x = projected.x;
        if (min_y > projected.y)
            min_y = projected.y;
        if (max_x < projected.x)
            max_x = projected.x;
        if (max_y < projected.y)
            max_y = projected.y;
    }
    return (max_x - min_x) * (max_y - min_y);
}
