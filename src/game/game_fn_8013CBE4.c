typedef struct Vec3 { float x, y, z; } Vec3;

extern void fn_80211A6C();
extern float fn_80211AF0(const Vec3*);
extern float fn_80211B44(const Vec3*, const Vec3*);
extern float lbl_8065031C;
extern float lbl_80650320;

float fn_8013CBE4(const Vec3* origin, const Vec3* endpoint,
                  const Vec3* point, Vec3* output, int clamp)
{
    Vec3 segment;
    Vec3 delta;
    float length;
    float amount;

    fn_80211A6C(endpoint, origin, &segment);
    length = fn_80211AF0(&segment);
    fn_80211A6C(point, origin, &delta);
    amount = fn_80211B44(&delta, &segment) / length;
    if (clamp != 0) {
        float maximum = amount > 0.0f ? amount : 0.0f;
        if (1.0f < maximum) {
            amount = 1.0f;
        } else {
            amount = amount > 0.0f ? amount : 0.0f;
        }
    }
    output->x = origin->x + segment.x * amount;
    output->y = origin->y + segment.y * amount;
    output->z = origin->z + segment.z * amount;
    return amount;
}
