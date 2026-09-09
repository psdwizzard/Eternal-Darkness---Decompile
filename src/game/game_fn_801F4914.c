typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    unsigned char pad[0x1C8];
    int mode;
} State;

extern State lbl_8030F540;
extern float lbl_80651348;
extern float lbl_8065134C;
extern float lbl_8064C394;
extern float lbl_8064C398;
extern void* lbl_8064C4E4;
extern Vec3 lbl_802FC678;

extern void fn_8011F114(Vec3*, void*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);

float fn_801F4914(void)
{
    float result = lbl_80651348;
    float distance = lbl_8064C394;

    if (lbl_8030F540.mode != -2) {
        result = lbl_8065134C;
    } else if (lbl_8064C4E4 != 0) {
        Vec3 transformed;
        Vec3 source;
        float length;

        fn_8011F114(&source, lbl_8064C4E4);
        transformed = source;
        fn_80211A6C(&lbl_802FC678, &transformed, &transformed);
        length = fn_80211B08(&transformed);
        if (distance > length) {
            float value;

            value = result = lbl_8065134C;
            value -= length / distance;
            value *= value;
            if (result < value) {
                result = lbl_8065134C;
            } else {
                result = value;
            }
        }
    }

    return result * lbl_8064C398;
}
