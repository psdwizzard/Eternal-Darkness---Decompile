extern void* lbl_80331720[6];
extern int lbl_8064CCD4;
extern int fn_801E8D24(void*);
extern void fn_8010C220(int, int, float);
extern double lbl_8064FE78;
extern float lbl_8064FE9C;

void fn_8010D888(short value)
{
    int offset;
    int index;

    switch (lbl_8064CCD4) {
    case 4:
        offset = fn_801E8D24(lbl_80331720[1]) * 2;
        index = fn_801E8D24(lbl_80331720[0]);
        index += offset;
        fn_8010C220(index, 0, (float)value / lbl_8064FE9C);
        break;
    }
}
