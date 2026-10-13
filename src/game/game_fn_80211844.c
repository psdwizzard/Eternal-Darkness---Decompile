typedef float Mtx44[4][4];

extern const float lbl_80651610;
extern const float lbl_80651614;
extern const float lbl_80651618;
extern const float lbl_8065161C;

/* Build a perspective projection matrix from the viewing frustum. */
void fn_80211844(Mtx44 m, float top, float bottom, float left,
                 float right, float near, float far)
{
    float reciprocal;
    float twiceNear;

    reciprocal = lbl_80651610 / (right - left);

    twiceNear = lbl_80651614 * near;
    m[0][0] = twiceNear * reciprocal;
    m[0][1] = lbl_80651618;
    m[0][2] = reciprocal * (right + left);
    m[0][3] = lbl_80651618;

    reciprocal = lbl_80651610 / (top - bottom);
    m[1][0] = lbl_80651618;
    twiceNear = lbl_80651614 * near;
    m[1][1] = twiceNear * reciprocal;
    m[1][2] = reciprocal * (top + bottom);
    m[1][3] = lbl_80651618;

    reciprocal = lbl_80651610 / (far - near);
    m[2][0] = lbl_80651618;
    m[2][1] = lbl_80651618;
    m[2][2] = -near * reciprocal;
    m[2][3] = reciprocal * -(far * near);

    m[3][0] = lbl_80651618;
    m[3][1] = lbl_80651618;
    m[3][2] = lbl_8065161C;
    m[3][3] = lbl_80651618;
}
