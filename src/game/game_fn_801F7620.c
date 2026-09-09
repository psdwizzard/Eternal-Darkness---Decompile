typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D7B8;
extern int lbl_8064D7B4;
extern float lbl_8064D7AC;
extern int lbl_8064D5A8;
extern const Vec3 lbl_8023B7C0;

extern void fn_801FA748(int, Vec3*);
extern void fn_801FA66C(int, int, float);
extern void fn_801F7804(void*);

void fn_801F7620(void* state)
{
    if (lbl_8064D7B8 == 0) {
        Vec3 value = lbl_8023B7C0;
        fn_801FA748(2, &value);
        *(void (**)(void*))((unsigned char*)state + 0x6C) = fn_801F7804;
    } else {
        if (lbl_8064D5A8 - lbl_8064D7B4 * (lbl_8064D5A8 / lbl_8064D7B4) == 0) {
            double amount = -(double)lbl_8064D7AC;
            lbl_8064D7AC = amount;
            fn_801FA66C(2, 0, (float)amount);
        }
        fn_801F7804(state);
        lbl_8064D7B8--;
    }
}
