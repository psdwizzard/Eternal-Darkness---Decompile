typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Pair {
    int x;
    int y;
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
    Pair projected;
    Vec3 axis;
    Vec3 scaled;
    Vec3 corners[4];
    Vec3 lower;
    Vec3 upper;
    Vec3 lower_margin;
    Vec3 upper_margin;
    Matrix matrix;
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    int i;

    fn_80211584(&matrix, first, third, second);
    fn_80211A6C(first, second, &axis);
    fn_80211B64(&axis, third, &scaled);
    fn_80211AAC(&scaled, &scaled);
    scaled.x *= lbl_806514D8;
    scaled.y *= lbl_806514D8;
    scaled.z *= lbl_806514D8;
    fn_80211A6C(fourth, &scaled, &lower);
    fn_80211A48(fourth, &scaled, &upper);
    lower_margin = upper;
    upper_margin = lower;
    lower_margin.y += margin;
    upper_margin.y += margin;
    fn_80211764(&matrix, &lower, corners, 4);
    fn_801F6BD8(corners, &projected, 1, 0);
    min_x = max_x = projected.x;
    min_y = max_y = projected.y;
    for (i = 1; i < 4; i++) {
        fn_801F6BD8(&corners[i], &projected, 1, 0);
        if (projected.x < min_x)
            min_x = projected.x;
        if (projected.y < min_y)
            min_y = projected.y;
        if (projected.x > max_x)
            max_x = projected.x;
        if (projected.y > max_y)
            max_y = projected.y;
    }
    return (max_x - min_x) * (max_y - min_y);
}
