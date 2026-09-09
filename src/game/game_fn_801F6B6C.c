typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned char lbl_8063C068[];
extern void fn_8017ACE0(void*, const Vec3*, Vec3*);
extern void fn_801F6BD8(const Vec3*, void*, int, int);

void fn_801F6B6C(const Vec3* input, void* output, int clamp, int shift)
{
    Vec3 transformed;

    fn_8017ACE0(lbl_8063C068, input, &transformed);
    fn_801F6BD8(&transformed, output, clamp, shift);
}
