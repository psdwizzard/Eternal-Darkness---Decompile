typedef struct Vec3 { float values[3]; } Vec3;
typedef struct Transform { Vec3 first, second, third, fourth; float scalar; } Transform;
extern Transform lbl_802FC6A0;

void fn_801F69BC(const Vec3* source)
{
    unsigned int x = ((const unsigned int*)source)[0];
    unsigned int y = ((const unsigned int*)source)[1];
    unsigned int z = ((const unsigned int*)source)[2];

    ((unsigned int*)&lbl_802FC6A0.fourth)[0] = x;
    ((unsigned int*)&lbl_802FC6A0.fourth)[1] = y;
    ((unsigned int*)&lbl_802FC6A0.fourth)[2] = z;
}
