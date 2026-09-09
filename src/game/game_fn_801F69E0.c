typedef struct Vec3 { float values[3]; } Vec3;
typedef struct Transform { Vec3 first, second, third, fourth; float scalar; } Transform;
extern Transform lbl_802FC6A0;

void fn_801F69E0(float value)
{
    lbl_802FC6A0.scalar = value;
}
