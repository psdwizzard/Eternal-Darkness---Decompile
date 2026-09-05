typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern volatile Vec3 lbl_80239530;
extern void fn_801FA748(int, Vec3*);

int fn_80088844(int unused)
{
    Vec3 direction;

    direction = lbl_80239530;
    fn_801FA748(2, &direction);
    return 1;
}
