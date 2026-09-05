typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *fn_80201BC8();
extern void fn_801F68B0(Vec3 *);
extern void fn_8012EC50(void *, int, Vec3 *, int, float, float);
extern float lbl_8064F290;

#pragma opt_common_subs off
void fn_800C92E8(void *object)
{
    Vec3 copy;
    Vec3 source;
    void *runtime = fn_80201BC8(object);

    fn_801F68B0(&source);
    copy = source;
    fn_8012EC50(runtime, 8, &copy, 1, lbl_8064F290, lbl_8064F290);
}
#pragma opt_common_subs reset
