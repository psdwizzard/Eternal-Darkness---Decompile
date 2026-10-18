typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Object8011F890 {
    char pad00[0x18];
    Vec3 value;
    float length;
    float saved_length;
} Object8011F890;

extern float PSVECMag(const Vec3* value);
extern void PSVECScale(Vec3* output, const Vec3* input, float scale);
extern const float lbl_80650068;
extern const float lbl_80650070;

void fn_8011F890(Object8011F890* object, float x, float y, float z)
{
    object->value.x = x;
    object->value.y = y;
    object->value.z = z;
    object->length = PSVECMag(&object->value);
    object->saved_length = object->length;
    if (lbl_80650068 != object->length) {
        PSVECScale(&object->value, &object->value,
                    lbl_80650070 / object->length);
    }
}
