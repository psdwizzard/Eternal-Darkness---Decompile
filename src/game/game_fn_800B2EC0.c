typedef signed char s8;

/* NonMatching: behavior-complete, size-exact reconstruction. The remaining
 * differences are equivalent branch layout and the compiler-local signed
 * integer-to-float conversion bias relocation. */
extern int lbl_8064CA3C;
extern int lbl_8064CA6C;
extern int lbl_8064CE44;
extern s8 lbl_8064CA31;
extern s8 lbl_8064CA30;
extern float lbl_8064CA18;
extern double lbl_8064F020;
extern float lbl_8064F01C;
extern int lbl_80247428[];

extern int fn_800B7EC0(void);
extern float fn_8017B4F4(void);
extern void fn_800B6E9C(int, int);
extern int fn_8017BB60(void);
extern int fn_800B194C(void);
extern void fn_800B81AC(void*, int, float);
extern int fn_8017BB98(void);

void fn_800B2EC0(int object)
{
    float value;
    int state;

    if (lbl_8064CA3C != 0) {
        return;
    }

    fn_800B7EC0();
    value = fn_8017B4F4();
    if (lbl_8064CA6C != 0) {
        fn_800B6E9C(object, lbl_8064CE44 & 4);
    }

    state = fn_8017BB60();
    switch (state) {
    case 0:
        fn_800B194C();
        if (lbl_8064CA31 != 0) {
            fn_800B81AC(lbl_80247428, object, lbl_8064CA18);
        }
        return;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    default:
        return;
    }

    if (lbl_8064CA31 != 0) {
        if (lbl_8064CA31 == 1) {
            value /= lbl_8064CA30;
            lbl_8064CA18 = value;
        } else if (lbl_8064CA31 == 2) {
            lbl_8064CA31 = 3;
            value = lbl_8064CA18;
        } else if (lbl_8064CA31 == 3) {
            value = lbl_8064CA18 + value / lbl_8064CA30;
        } else if (lbl_8064CA31 == 4) {
            lbl_8064CA31 = 5;
            value = lbl_8064F01C;
            lbl_8064CA18 = value;
        } else {
            value = lbl_8064F01C;
        }
    }

    if (fn_8017BB98() != 3) {
        fn_800B81AC(lbl_80247428, object, value);
    }
}
