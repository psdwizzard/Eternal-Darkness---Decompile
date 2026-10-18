typedef unsigned char u8;
typedef signed char s8;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Vec3 { float x, y, z; } Vec3;

extern Color lbl_8064EEE0, lbl_8064EEE4, lbl_8064EEE8, lbl_8064EEEC, lbl_8064EEF0;
extern Color lbl_80651A2C, lbl_80651A30, lbl_80651A34;
extern Vec3 lbl_802396F0[];
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_8012CBE8(u8 *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_8012C478(u8 *, int, int);

void fn_800A4AC4(u8 *object, int selector, int mode, int alternate)
{
    register Vec3 *vectors = &lbl_802396F0[1];
    Color color = lbl_8064EEE0;
    Color delta = lbl_80651A2C;
    Vec3 first = vectors[0];
    Vec3 second = vectors[1];
    Vec3 third = vectors[2];
    Vec3 zero = vectors[3];

    if (mode == 2) {
        Vec3 a, b, c;
        if (alternate == 0) {
            first = third;
            second = zero;
            third = zero;
        }
        c = third;
        b = second;
        a = first;
        fn_8012CBE8(object, selector, &a, &b, &c, 0);
    } else if (mode == 1) {
        Color c, b, a;
        a = color;
        b = delta;
        c = color;
        fn_8012C62C(object, selector, &c, (s8 *)&b, &a, 2);
    } else if (mode == 3) {
        fn_8012C478(object, selector, 0);
    } else if (alternate == 0) {
        Color c, b, a;
        a = lbl_8064EEE8;
        b = lbl_80651A30;
        c = lbl_8064EEE4;
        fn_8012C62C(object, selector, &c, (s8 *)&b, &a, 4);
    } else {
        Color c, b, a;
        a = lbl_80651A34;
        b = lbl_8064EEF0;
        c = lbl_8064EEEC;
        fn_8012C62C(object, selector, &c, (s8 *)&b, &a, 4);
    }
}
