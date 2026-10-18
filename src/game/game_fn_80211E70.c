typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

extern void PSVECNormalize(Vec3 *in, Vec3 *out);
extern float sinf(float value);
extern float cosf(float value);
extern float lbl_80651654;

/* Converts an axis and angle to a quaternion. */
void C_QUATRotAxisRad(Quaternion *out, Vec3 *axis, float angle)
{
    Vec3 unitAxis;
    float sine, cosine;

    PSVECNormalize(axis, &unitAxis);
    angle = lbl_80651654 * angle;
    sine = sinf(angle);
    cosine = cosf(angle);
    out->x = sine * unitAxis.x;
    out->y = sine * unitAxis.y;
    out->z = sine * unitAxis.z;
    out->w = cosine;
}
