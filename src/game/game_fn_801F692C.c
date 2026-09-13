typedef struct Vec3 { float values[3]; } Vec3;
typedef struct Transform { Vec3 first, second, third, fourth; float scalar; } Transform;
extern Transform lbl_802FC6A0;

void fn_801F692C(Vec3 source)
{
    lbl_802FC6A0.first = source;
}
