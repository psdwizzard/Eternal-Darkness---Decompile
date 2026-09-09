typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern Vec3 lbl_802FC6A0;
extern void fn_80178F14(int, int, int, int, int, int);

void fn_801F6D90(int arg0, int arg1, int arg2)
{
    fn_80178F14(arg0, arg1, arg2, (int)lbl_802FC6A0.x,
                (int)lbl_802FC6A0.y, (int)lbl_802FC6A0.z);
}
