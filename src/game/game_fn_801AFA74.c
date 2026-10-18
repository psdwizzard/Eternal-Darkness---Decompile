typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float lbl_80650E98;
extern float lbl_80650E9C;

extern void fn_801F68B0(Vec3*);
extern void fn_801F68F8(Vec3*);
extern float fn_800490E8(float, float);
extern float cosf(float);
extern float sinf(float);
extern double fn_800B811C(double);
extern int fn_801AF9B0(int, int, int);

void fn_801AFA74(Vec3* position, int* out_x, int* out_y)
{
    Vec3 first;
    Vec3 second;
    Vec3 source_first;
    Vec3 source_second;
    float delta_x;
    float delta_y;
    float angle;
    float difference;
    float cosine;
    float sine;
    int desired_x;
    int desired_y;
    int ix;
    int iy;
    int distance;
    int x;
    int y;

    fn_801F68B0(&source_first);
    first = source_first;
    fn_801F68F8(&source_second);
    second = source_second;

    delta_x = position->x - first.x;
    delta_y = position->y - first.y;
    angle = fn_800490E8(delta_x, delta_y);
    difference = angle - fn_800490E8(second.x - first.x,
                                     second.y - first.y);
    cosine = cosf(difference);
    sine = sinf(difference);
    desired_x = (int)(lbl_80650E98 * sine) + 64;
    desired_y = (int)(lbl_80650E98 * cosf(lbl_80650E9C + difference)) + 64;

    distance = (int)fn_800B811C((int)delta_x * (int)delta_x +
                                 (int)delta_y * (int)delta_y);
    x = (int)((float)distance * sine);
    y = (int)((float)distance * cosine);

    x = x < 0 ? -x : x;
    y = y < 0 ? -y : y;

    desired_x = fn_801AF9B0(x, 64, desired_x);
    desired_y = fn_801AF9B0(y, 64, desired_y);
    if (out_x != 0) {
        *out_x = desired_x;
    }
    if (out_y != 0) {
        *out_y = desired_y;
    }
}
