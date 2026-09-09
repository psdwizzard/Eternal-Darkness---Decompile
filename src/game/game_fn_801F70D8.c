typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void* lbl_8064C4E4;
extern Vec3 lbl_8023B7A8;
extern float lbl_80651464;
extern void fn_8011F114(Vec3*, void*);
extern float fn_800ED720(float);
extern void* memcpy(void*, const void*, unsigned long);

void fn_801F70D8(unsigned char* state, int enabled)
{
    if (lbl_8064C4E4 != 0 && enabled != 0) {
        Vec3 direction = lbl_8023B7A8;
        Vec3 source;
        float length;

        if (*(void**)(state + 0x74) != 0) {
            source = **(Vec3**)(state + 0x74);
        } else {
            fn_8011F114(&source, lbl_8064C4E4);
        }

        direction.x = *(float*)(state + 0) - source.x;
        direction.y = *(float*)(state + 4) - source.y;
        direction.z = *(float*)(state + 8) - source.z;
        length = fn_800ED720(direction.x * direction.x +
                             direction.y * direction.y +
                             direction.z * direction.z);
        if (lbl_80651464 != length) {
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;
            memcpy(state + 0x54, &direction, 0xC);
        } else {
            enabled = 0;
        }
    }
    *(int*)(state + 0x3C) = enabled;
}
