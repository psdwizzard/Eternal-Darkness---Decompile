typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float fn_8012B7D0(void *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8012B7A0(void *, float);
extern void fn_8017A12C(float *, float, float);
extern void fn_8017A010(float *, float, float, float, int);
extern float lbl_8064F21C;
extern float lbl_8064F24C;

void fn_800C849C(void *object, Vec3 *position, float step)
{
    Vec3 copy = *position;
    float target = fn_8012B7D0(object, &copy);
    float current = fn_8012B750(object);
    float difference;
    fn_8017A12C(&difference, current, target);
    if ((difference < lbl_8064F21C ? -difference : difference) > lbl_8064F24C) {
        fn_8017A010(&current, target, step, lbl_8064F24C, 0);
        fn_8012B7A0(object, current);
    }
}
