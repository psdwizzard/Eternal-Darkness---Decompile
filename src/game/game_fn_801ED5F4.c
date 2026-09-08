typedef signed short s16;
typedef unsigned char u8;

typedef float Matrix34[3][4];

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern float lbl_8064D620;
extern int lbl_8064D624;
extern int lbl_8064D628;
extern int lbl_8064D668;
extern int lbl_8064CBA4;

extern float lbl_80651318;
extern float lbl_8065131C;
extern double lbl_80651320;
extern float lbl_80651328;
extern float lbl_8065132C;
extern float lbl_80651330;
extern float lbl_80651334;
extern float lbl_80651338;
extern float lbl_8065133C;
extern float lbl_80651340;

extern int fn_8011FF38(int);
extern void fn_801ECAAC(Color*);
extern void fn_801EDA68(s16*, float*);
extern void fn_80210FDC(Matrix34, Matrix34, Matrix34);
extern void fn_80211484(Matrix34, float, float, float);
extern void fn_80226D28(int);
extern void fn_8022B748(Matrix34, int, int);
extern void* memset(void*, int, unsigned int);

void fn_801ED5F4(int object, int flags, s16 value, float* direction,
                 Matrix34 input, float alpha)
{
    Color color;
    Matrix34 transform;
    Matrix34 temporary;
    float divisor;
    int changed;

    if (object != 0 && fn_8011FF38(object) != 0) {
        changed = 0;
        memset(&color, 0, sizeof(color));
        lbl_8064D628 = object;

        switch (flags & 0xE003) {
        case 1:
            flags |= 4;
            flags &= ~0x1800;
            fn_80211484(temporary, alpha, lbl_80651318, lbl_80651318);
            transform[0][0] = lbl_80651328;
            transform[0][1] = lbl_80651318;
            transform[0][2] = lbl_80651318;
            transform[0][3] = lbl_80651318;
            transform[1][0] = lbl_80651318;
            transform[1][1] = lbl_80651318;
            transform[1][2] = lbl_80651318;
            transform[1][3] = lbl_80651318;
            fn_80210FDC(transform, temporary, transform);
            fn_80226D28(0);
            alpha = lbl_8065131C;
            changed = 1;
            break;
        case 0x4000:
            flags |= 4;
            flags &= ~0x1800;
            transform[0][0] = -direction[0] / lbl_8065132C;
            transform[0][1] = -direction[1] / lbl_8065132C;
            transform[0][2] = -direction[2] / lbl_8065132C;
            transform[1][0] = alpha / lbl_8065132C;
            transform[1][1] = lbl_80651318;
            transform[1][2] = lbl_80651318;
            transform[1][3] = lbl_80651318;
            fn_80210FDC(transform, input, transform);
            fn_80226D28(0);
            alpha = lbl_8065131C;
            changed = 1;
            break;
        case 2:
        case 0x2000:
        case 0x8000:
            fn_801EDA68(&value, &divisor);
            if (flags & 0x400) {
                changed = 1;
                transform[0][0] = lbl_8065131C / divisor;
                transform[0][1] = lbl_80651330 / divisor;
                transform[0][2] = lbl_80651318;
                transform[0][3] = lbl_80651318;
                transform[1][0] = lbl_80651334 / divisor;
                transform[1][1] = lbl_80651318;
                transform[1][2] = lbl_80651318;
                transform[1][3] = lbl_80651318;
            } else if (lbl_8064D620 != divisor) {
                float scale = lbl_80651338 / divisor;
                changed = 1;
                transform[0][0] = scale;
                transform[0][1] = scale;
                transform[0][2] = lbl_80651318;
                transform[0][3] = lbl_80651318;
                transform[1][0] = lbl_80651318;
                transform[1][1] = lbl_80651318;
                transform[1][2] = scale;
                transform[1][3] = scale;
            }
            break;
        }

        if (lbl_8064CBA4 == 1) {
            transform[0][0] *= lbl_8065133C;
            transform[1][0] *= lbl_8065133C;
        }

        switch (flags & 0x1F8) {
        case 0x20:
            color.r = 0xFF;
            break;
        case 0x10:
            color.g = 0xFF;
            break;
        case 8:
            color.b = 0xFF;
            color.g = 0x89;
            color.r = 0x49;
            break;
        case 0x40:
            color.b = 0xFF;
            color.r = 0xFF;
            break;
        case 0x80:
            color.b = 0xFF;
            color.g = 0xFF;
            color.r = 0xFF;
            break;
        case 0x100:
            color.g = 0xFF;
            color.r = 0xFF;
            break;
        default:
            color.r = color.g = color.b = 0;
            break;
        }

        if (flags & 4) {
            if (flags & 0x800)
                color.a = (u8)(lbl_80651340 * alpha);
            else if (flags & 0x1000)
                color.a = (u8)(lbl_80651340 * (lbl_8065131C - alpha));
            else
                color.a = 0xFF;
        } else {
            color.a = 0;
        }

        color.r = (u8)(color.r * alpha);
        color.g = (u8)(color.g * alpha);
        color.b = (u8)(color.b * alpha);
        fn_801ECAAC(&color);

        if (lbl_8064D624 != flags || changed != 0) {
            lbl_8064D624 = flags;
            fn_8022B748(transform, 0x33, 1);
        }
    } else if (object == 0) {
        lbl_8064D628 = object;
        lbl_8064D624 = -1;
        lbl_8064D620 = lbl_80651318;
        fn_80226D28(1);
    }

    lbl_8064D668 = 0;
}
