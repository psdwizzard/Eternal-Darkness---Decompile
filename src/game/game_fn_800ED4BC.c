typedef unsigned int u32;
typedef signed short s16;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

typedef struct Color {
    unsigned char r, g, b, a;
} Color;

typedef struct Vector {
    float x;
    float y;
    float z;
} Vector;

typedef struct ScreenPosition {
    int x;
    int y;
    int z;
} ScreenPosition;

extern void fn_801F6B6C(Vector*, ScreenPosition*, int, int);
extern u32 fn_801F6D90(int, int, int);
extern int fn_800F9E2C(char*, const char*, void*);
extern void fn_801E3AA4(int);
extern u32 fn_801E3A34(Color);
extern int fn_801E5AD0(int);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(float, const char*, ...);
extern void fn_801ED3F4(int);
extern void fn_8022B4B8(void*, int);
extern void fn_801ECC4C(void);

extern Color lbl_802FC5BC[];
extern char lbl_8063BF28[];
extern int lbl_8064D5FC;

static inline float clamp_scale(float value)
{
    float minimum = 0.2f;
    float result;

    if (value > minimum) {
        minimum = value;
    }
    result = 3.0f;
    result = result < minimum ? result : (value > 0.2f ? value : 0.2f);
    return result;
}

void fn_800ED4BC(Vector* position, int colorIndex, const char* format, ...)
{
    char buffer[360];
    Vector source;
    ScreenPosition screen;
    va_list args;
    Color oldColor;
    u32 distance;
    float scale;
    int savedFont;
    int savedState;

    source.x = position->x;
    source.y = position->y;
    source.z = position->z;
    fn_801F6B6C(&source, &screen, 0, 0);
    distance = fn_801F6D90((int)position->x, (int)position->y, (int)position->z);
    if (distance != 0 && screen.z != 0 && screen.x > 0 && screen.x < 640 &&
        screen.y > 0 && screen.y < 480) {
        va_start(args, format);
        fn_800F9E2C(buffer, format, args);
        scale = clamp_scale(1000.0f / (float)distance);
        savedState = lbl_8064D5FC;
        fn_801E3AA4(0);
        *(u32*)&oldColor = fn_801E3A34(lbl_802FC5BC[colorIndex]);
        savedFont = fn_801E5AD0(0x63);
        fn_801E5430((s16)screen.x, (s16)screen.y);
        fn_801E56AC(scale, buffer);
        fn_801E3A34(oldColor);
        fn_801E5AD0(savedFont);
        fn_801ED3F4(savedState);
        fn_8022B4B8(lbl_8063BF28, 0);
        fn_801ECC4C();
    }
}
