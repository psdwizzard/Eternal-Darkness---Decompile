typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned int fn_800FBFB0(void);
extern const float lbl_8064E79C;
extern const float lbl_8064E7C8;

void fn_8006AFA0(Vec3 *out, const Vec3 *position)
{
    Vec3 adjusted = *position;

    adjusted.z += lbl_8064E79C + (float)(int)(fn_800FBFB0() & 0x1F);
    adjusted.x += lbl_8064E7C8 - (float)(int)(fn_800FBFB0() & 0xF);
    adjusted.y += lbl_8064E7C8 - (float)(int)(fn_800FBFB0() & 0xF);
    *out = adjusted;
}
