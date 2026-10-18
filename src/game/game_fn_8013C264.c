typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void PSVECSubtract();
extern float PSVECMag(const Vec3*);
extern void PSVECScale(Vec3*, const Vec3*, float);
extern float fn_8013C418(const Vec3*, const Vec3*, const Vec3*, Vec3*);
extern float lbl_8065031C;
extern float lbl_80650320;

void fn_8013C264(const Vec3* first, const Vec3* second, Vec3* direction,
                 const Vec3* origin, Vec3* output)
{
    const Vec3* second_ptr;
    Vec3* direction_ptr;
    float distance;
    float amount;

    second_ptr = second;
    direction_ptr = direction;
    PSVECSubtract((Vec3*)second_ptr, first);
    distance = PSVECMag(direction_ptr);
    if (lbl_8065031C != distance) {
        PSVECScale(direction_ptr, direction_ptr, lbl_80650320 / distance);
        amount = fn_8013C418(origin, first, direction_ptr, output);
        if (amount < lbl_8065031C) {
            *output = *first;
        } else if (amount > distance) {
            *output = *second_ptr;
        }
    } else {
        *output = *first;
    }
}
