typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D18C;
extern float lbl_8064F7F4;
extern const float lbl_8064F7F8;
extern int fn_8011FF38(void *);
extern void *fn_80201BC8();
extern void fn_8011F114();
extern void fn_8011FEDC(void *, int);
extern void fn_8011FEFC(void *, int);
extern void fn_8011FEEC(void *, float);
extern unsigned int fn_8011FA8C(void *, int, int);
extern void fn_801AAE68(float, int, int, int, Vec3 *, int, int, int, unsigned short, int);

void fn_800E828C(void *object, int value, int enabled, float scale)
{
    if (fn_8011FF38(object) != 0) {
        void *state = fn_80201BC8(object);
        Vec3 position;
        float intensity;
        int room;

        fn_8011F114(&position, state);
        fn_8011FEDC(state, value);
        if ((unsigned char)enabled != 0) {
            fn_8011FEFC(state, enabled);
        }
        if (scale != lbl_8064F7F4) {
            fn_8011FEEC(state, scale);
        }
        fn_8011FA8C(state, 0, 0x20000000);
        intensity = lbl_8064F7F8;
        room = lbl_8064D18C;
        fn_801AAE68(intensity, 497, 100, 0, &position, 2, 2, 0,
                    (unsigned short)room, 0);
    }
}
