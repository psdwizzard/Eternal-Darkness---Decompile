typedef unsigned int u32;

extern volatile int lbl_80251200[3];
extern void* fn_80201814(u32);
extern void* fn_80201BC8(void*);
extern float fn_8012B750(void*);
extern void fn_8017A12C(float*, float, float);
extern float fn_80179F20(float);
extern void fn_801A69F0(int);
extern float lbl_80650DCC;
extern float lbl_80650DD0;

void fn_801A68C4(void* state)
{
    unsigned char* data = state;
    void* first = 0;
    void* second = 0;
    float difference;
    int active;
    void* object;
    int pass;

    if (*(int*)(data + 0x98) != 0) {
        active = *(int*)(data + 0x9C);
        if (active != 0) {
            /* The counted dispatch preserves the retail branch pair.
               Volatile slot reads keep the short-circuit load ordering. */
            for (pass = 0; pass < 1; ++pass) {
                if (lbl_80251200[0] || lbl_80251200[1] || lbl_80251200[2])
                    goto active_path;
            }
            return;
active_path:
            object = fn_80201814(active);
            if (object != 0) {
                first = fn_80201BC8(object);
            }
            object = fn_80201814(*(u32*)(data + 0x98));
            if (object != 0) {
                second = fn_80201BC8(object);
            }
            if (first != 0 && second != 0) {
                float first_angle = fn_8012B750(first);
                float second_angle = fn_8012B750(second);
                fn_8017A12C(&difference, first_angle, second_angle);
                difference = fn_80179F20(difference);
                fn_801A69F0(difference < lbl_80650DCC || difference > lbl_80650DD0);
            }
        }
    }
}
