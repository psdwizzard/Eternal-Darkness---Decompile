typedef unsigned char u8;
typedef unsigned int u32;

extern volatile u8 lbl_8064C368;
extern volatile float lbl_8064D5D8;
extern float lbl_8064D5DC;
extern float lbl_8064CF04;
extern float lbl_8064CF08;

extern void fn_801E7EFC(void);
extern void PERFEventEnd(int);
extern void fn_801EAA04(float, float);

void fn_80024468(void)
{
    float first;
    float second;
    u32 mode;

    fn_801E7EFC();
    first = lbl_8064D5D8;
    mode = lbl_8064C368;
    second = lbl_8064D5DC;
    lbl_8064CF08 = first;
    lbl_8064CF04 = second;
    if (mode == 0) {
        PERFEventEnd(0);
    } else if (lbl_8064C368 != 2) {
        fn_801EAA04(lbl_8064D5DC, lbl_8064D5D8);
    }
}
