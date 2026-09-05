typedef struct Vec3 { float x, y, z; } Vec3;

extern float fn_80211B44(const Vec3*, const Vec3*);
extern float fn_800ED720(float);
extern float lbl_8065031C;
extern float lbl_80650324;
extern float lbl_80650328;

void fn_8013C518(Vec3* position, const Vec3* direction,
                 float radius, float limit)
{
    float amount;
    float length;

    amount = limit + fn_80211B44(direction, position);
    amount = -amount;
    if (amount > -(lbl_80650324 + radius)) {
        amount = lbl_80650328 + (amount + radius);
        length = fn_800ED720(direction->x * direction->x
                           + direction->y * direction->y);
        if (lbl_8065031C != length) {
            position->x += amount * (direction->x / length);
            position->y += amount * (direction->y / length);
        }
    }
}
