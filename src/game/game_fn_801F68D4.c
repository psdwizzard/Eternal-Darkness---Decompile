typedef struct Vec3 { float values[3]; } Vec3;
typedef struct Transform {
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 fourth;
    float scalar;
} Transform;

extern Transform lbl_802FC6A0;

void fn_801F68D4(Vec3* destination)
{
    *destination = lbl_802FC6A0.fourth;
}
