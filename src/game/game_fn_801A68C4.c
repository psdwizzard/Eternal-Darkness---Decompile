typedef unsigned int u32;

extern int lbl_80251200[3];
extern void* fn_80201814(u32);
extern void* fn_80201BC8(void*);
extern float fn_8012B750(void*);
extern void fn_8017A12C(float*, float, float);
extern float fn_80179F20(float);
extern void fn_801A69F0(int);

void fn_801A68C4(void* state)
{
    /* NonMatching: GC/1.3 folds the final zero test below into a single beq;
       retail retains bne to the active path followed by b to the epilogue. */
    unsigned char* data = state;
    void* first = 0;
    void* second = 0;
    float difference;
    int active;
    void* object;

    if (*(int*)(data + 0x98) != 0) {
      active = *(int*)(data + 0x9C);
      if (active != 0) {
       if (lbl_80251200[0] == 0 && lbl_80251200[1] == 0 &&
           lbl_80251200[2] == 0)
           return;
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
            fn_801A69F0(difference < 0.0f || difference > 3.1415927f);
        }
      }
      }
}
