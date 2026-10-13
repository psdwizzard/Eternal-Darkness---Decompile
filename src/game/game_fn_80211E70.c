typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

extern void fn_80211AAC(Vec3 *in, Vec3 *out);
extern float fn_80048C2C(float value);
extern float fn_80048C50(float value);
extern float lbl_80651654;

/* Converts an axis and angle to a quaternion. */
void fn_80211E70(Quaternion *out, Vec3 *axis, float angle)
{
    Vec3 unitAxis;
    float sine, cosine;

    fn_80211AAC(axis, &unitAxis);
    angle = lbl_80651654 * angle;
    sine = fn_80048C2C(angle);
    cosine = fn_80048C50(angle);
    out->x = sine * unitAxis.x;
    out->y = sine * unitAxis.y;
    out->z = sine * unitAxis.z;
    out->w = cosine;
}
