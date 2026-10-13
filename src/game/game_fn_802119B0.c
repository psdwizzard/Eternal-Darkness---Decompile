typedef float Mtx44[4][4];

extern const float lbl_80651610;
extern const float lbl_80651614;
extern const float lbl_80651618;
extern const float lbl_8065161C;

/* Build an orthographic projection matrix from the viewing volume. */
void fn_802119B0(Mtx44 m, float top, float bottom, float left,
                 float right, float near, float far)
{
    float reciprocal = lbl_80651610 / (right - left);

    m[0][0] = lbl_80651614 * reciprocal;
    m[0][1] = lbl_80651618;
    m[0][2] = lbl_80651618;
    m[0][3] = reciprocal * -(right + left);

    reciprocal = lbl_80651610 / (top - bottom);
    m[1][0] = lbl_80651618;
    m[1][1] = lbl_80651614 * reciprocal;
    m[1][2] = lbl_80651618;
    m[1][3] = reciprocal * -(top + bottom);

    reciprocal = lbl_80651610 / (far - near);
    m[2][0] = lbl_80651618;
    m[2][1] = lbl_80651618;
    m[2][2] = lbl_8065161C * reciprocal;
    m[2][3] = -far * reciprocal;

    m[3][0] = lbl_80651618;
    m[3][1] = lbl_80651618;
    m[3][2] = lbl_80651618;
    m[3][3] = lbl_80651610;
}
