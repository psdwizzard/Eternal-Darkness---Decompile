typedef struct Vec3 { float x, y, z; } Vec3;

extern float fn_80211B08(const Vec3* value);
extern void fn_80211A90(Vec3* output, const Vec3* input, float scale);
extern float lbl_80650068;
extern float lbl_80650070;

void fn_8011F808(void* object, Vec3* value)
{
    char* bytes = object;
    *(Vec3*)(bytes + 0x18) = *value;
    *(float*)(bytes + 0x24) = fn_80211B08(value);
    *(float*)(bytes + 0x28) = fn_80211B08(value);
    if (lbl_80650068 != *(float*)(bytes + 0x24)) {
        fn_80211A90((Vec3*)(bytes + 0x18), (Vec3*)(bytes + 0x18),
                    lbl_80650070 / *(float*)(bytes + 0x24));
    }
}
