typedef struct Vec3 { float x, y, z; } Vec3;

extern float fn_80211B44(const Vec3*, const Vec3*);
extern float lbl_80650324;
extern float lbl_80650328;

void fn_8013C460(Vec3* position, const Vec3* direction,
                 float radius, float limit)
{
    float amount;

    amount = limit + fn_80211B44(position, direction);
    amount = -amount;
    if (amount > -(lbl_80650324 + radius)) {
        amount = lbl_80650328 + (amount + radius);
        position->x += amount * direction->x;
        position->y += amount * direction->y;
        position->z += amount * direction->z;
    }
}
