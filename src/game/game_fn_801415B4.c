typedef unsigned char u8;
typedef signed short s16;

extern u8 lbl_8064D020;
extern s16 lbl_8064D022;
extern s16 lbl_8064D024;

static float corner_a[2][3];
static float corner_b[2][3];
static float corner_c[2][3];

#define V0 (corner_b[lbl_8064D020])
#define V1 (corner_a[lbl_8064D020])
#define V2 (corner_c[lbl_8064D020])

#define EDGE_EDGE_TEST(P0, Q0, Q1)                                         \
    Bx = Q0[i0] - Q1[i0];                                                  \
    By = Q0[i1] - Q1[i1];                                                  \
    Cx = P0[i0] - Q0[i0];                                                  \
    Cy = P0[i1] - Q0[i1];                                                  \
    f = Ay * Bx - Ax * By;                                                 \
    d = By * Cx - Bx * Cy;                                                 \
    if ((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f)) {      \
        e = Ax * Cy - Ay * Cx;                                             \
        if (f > 0) {                                                       \
            if (e >= 0 && e <= f) {                                        \
                return 1;                                                  \
            }                                                              \
        } else {                                                           \
            if (e <= 0 && e >= f) {                                        \
                return 1;                                                  \
            }                                                              \
        }                                                                  \
    }

#define EDGE_AGAINST_TRI_EDGES(P0, P1, Q0, Q1, Q2)                         \
    {                                                                      \
        float Ax, Ay, Bx, By, Cx, Cy, e, d, f;                             \
        Ax = P1[i0] - P0[i0];                                              \
        Ay = P1[i1] - P0[i1];                                              \
        EDGE_EDGE_TEST(P0, Q0, Q1);                                        \
        EDGE_EDGE_TEST(P0, Q1, Q2);                                        \
        EDGE_EDGE_TEST(P0, Q2, Q0);                                        \
    }

#define POINT_IN_TRI(P0, Q0, Q1, Q2)                                       \
    {                                                                      \
        float a, b, c, d0, d1, d2;                                         \
        a = Q1[i1] - Q0[i1];                                               \
        b = -(Q1[i0] - Q0[i0]);                                            \
        c = -a * Q0[i0] - b * Q0[i1];                                      \
        d0 = a * P0[i0] + b * P0[i1] + c;                                  \
        a = Q2[i1] - Q1[i1];                                               \
        b = -(Q2[i0] - Q1[i0]);                                            \
        c = -a * Q1[i0] - b * Q1[i1];                                      \
        d1 = a * P0[i0] + b * P0[i1] + c;                                  \
        a = Q0[i1] - Q2[i1];                                               \
        b = -(Q0[i0] - Q2[i0]);                                            \
        c = -a * Q2[i0] - b * Q2[i1];                                      \
        d2 = a * P0[i0] + b * P0[i1] + c;                                  \
        if (d0 * d1 > 0.0) {                                               \
            if (d0 * d2 > 0.0) {                                           \
                return 1;                                                  \
            }                                                              \
        }                                                                  \
    }

int fn_801415B4(const float* U0, const float* U1, const float* U2)
{
    int i0 = lbl_8064D024;
    int i1 = lbl_8064D022;

    EDGE_AGAINST_TRI_EDGES(V0, V1, U0, U1, U2);
    EDGE_AGAINST_TRI_EDGES(V1, V2, U0, U1, U2);
    EDGE_AGAINST_TRI_EDGES(V2, V0, U0, U1, U2);
    POINT_IN_TRI(V0, U0, U1, U2);
    POINT_IN_TRI(U0, V0, V1, V2);
    return 0;
}
