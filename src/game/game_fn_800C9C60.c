typedef signed short s16;

extern float lbl_8064F29C;
extern double lbl_8064F2A0;

extern void *fn_80201BC8();
extern int fn_80038308(void *, int, s16 *);
extern int fn_80038464(void *, int, s16 *);
extern int fn_80201B64(void *);
extern void fn_80121104(void *, float);
extern float fn_8012110C(void *);

float fn_800C9C60(void *object)
{
    void *runtime;
    s16 first;
    s16 second;
    float result = lbl_8064F29C;

    if (object != 0 && (runtime = fn_80201BC8(object)) != 0 &&
        fn_80038308(object, 0, &first) != 0 &&
        fn_80038464(object, 0, &second) != 0) {
        int kind = fn_80201B64(object);
        if (kind != 8 && kind != 9) {
            float ratio;
            if (second != 0) {
                ratio = (float)first / (float)second;
            } else {
                ratio = lbl_8064F29C;
            }
            result = ratio;
            fn_80121104(runtime, result);
        } else {
            result = fn_8012110C(runtime);
        }
    }
    return result;
}
