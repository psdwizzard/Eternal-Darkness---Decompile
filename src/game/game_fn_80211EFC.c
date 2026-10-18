typedef int s32;
typedef float f32;
typedef f32 Mtx[3][4];

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

typedef struct NextAxis {
    s32 idx[3];
} NextAxis;

extern const NextAxis lbl_8023B8D0;
extern const f32 lbl_8065163C;
extern double lbl_80651640;
extern double lbl_80651648;
extern f32 lbl_80651650;
extern f32 lbl_80651654;
extern double __frsqrte(double);

static inline f32 sqrtf(f32 x)
{
    volatile f32 y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        double t;
        t = x * (guess * guess);
        guess = lbl_80651640 * guess * (lbl_80651648 - t);
        t = x * (guess * guess);
        guess = lbl_80651640 * guess * (lbl_80651648 - t);
        t = x * (guess * guess);
        guess = lbl_80651640 * guess * (lbl_80651648 - t);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

/* Converts a rotation matrix to a quaternion (C_QUATMtx). */
void C_QUATMtx(Quaternion* r, Mtx m)
{
    f32 tr, s, inv;
    s32 i, j, k;
    NextAxis nxt = lbl_8023B8D0;
    f32 q[3];

    tr = m[0][0] + m[1][1] + m[2][2];
    if (tr > 0.0f) {
        s = sqrtf(lbl_80651650 + tr);
        inv = lbl_80651654 / s;
        r->w = lbl_80651654 * s;
        r->x = inv * (m[2][1] - m[1][2]);
        r->y = inv * (m[0][2] - m[2][0]);
        r->z = inv * (m[1][0] - m[0][1]);
    } else {
        i = 0;
        if (m[1][1] > m[0][0]) {
            i = 1;
        }
        if (m[2][2] > m[i][i]) {
            i = 2;
        }
        j = nxt.idx[i];
        k = nxt.idx[j];
        s = sqrtf(lbl_80651650 + (m[i][i] - (m[j][j] + m[k][k])));
        q[i] = lbl_80651654 * s;
        if (0.0f != s) {
            s = lbl_80651654 / s;
        }
        r->w = s * (m[k][j] - m[j][k]);
        q[j] = s * (m[i][j] + m[j][i]);
        q[k] = s * (m[i][k] + m[k][i]);
        r->x = q[0];
        r->y = q[1];
        r->z = q[2];
    }
}
