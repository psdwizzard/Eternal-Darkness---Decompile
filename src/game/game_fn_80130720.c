typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Object Object;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern int lbl_8064CF30;
extern Object* lbl_8064C4E4;
extern u8 lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern float lbl_80650218;
extern float lbl_8065021C;

extern void fn_80125ECC(void*);
extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECF50(int);
extern void fn_80226C18(int, int);
extern void fn_801ECD74(Color*);
extern void fn_80226AB4(int, int, int);
extern void fn_80130980(void);
extern void fn_80130984(float, float, float);
extern void fn_800EBA80(int, Vec3*, Color*, int, float);

static Vec3 point0 = {0};
static Vec3 point1 = {0};
static Vec3 point2 = {0};
static Vec3 point3 = {0};
static Vec3 point4 = {0};
static Vec3 point5 = {0};
static Vec3 point6 = {0};
static Vec3 point7 = {0};
static Vec3 point8 = {0};
static Vec3 point9 = {0};

void fn_80130720(Object* object)
{
    Color first_source;
    Color first_color;
    Color second_color;
    Color third_color;
    Color fourth_color;
    Color effect_color_a;
    Color effect_color_b;
    Color final_color;
    Color second_source;

    fn_80125ECC(object);
    if (lbl_8064CF30 != 0) {
        if (object == lbl_8064C4E4) {
            fn_801ED468(27);
            fn_80226D28(0);
            fn_801ED118();
            fn_801EDA7C(lbl_802FC53C, 0, 703, 0);
            fn_801ECF50(4);
            fn_80226C18(18, 0);

            first_source = lbl_802FC5BC[5];
            first_source.a = 0xFF;
            first_color = first_source;
            fn_801ECD74(&first_color);
            fn_80226AB4(168, 3, 2);
            fn_80130984(point7.x, point7.y, point7.z);
            fn_80130984(point8.x, point8.y, point8.z);
            fn_80130980();

            second_color = second_source = lbl_802FC5BC[7];
            fn_801ECD74(&second_color);
            fn_80226AB4(168, 3, 2);
            fn_80130984(point3.x, point3.y, point3.z);
            fn_80130984(point4.x, point4.y, point4.z);
            fn_80130980();

            third_color = lbl_802FC5BC[8];
            fn_801ECD74(&third_color);
            fn_80226AB4(168, 3, 2);
            fn_80130984(point1.x, point1.y, point1.z);
            fn_80130984(point2.x, point2.y, point2.z);
            fn_80130980();

            fourth_color = lbl_802FC5BC[11];
            fn_801ECD74(&fourth_color);
            fn_80226AB4(168, 3, 2);
            fn_80130984(point5.x, point5.y, point5.z);
            fn_80130984(point6.x, point6.y, point6.z);
            fn_80130980();

            effect_color_a = lbl_802FC5BC[13];
            fn_800EBA80(0, &point0, &effect_color_a, 100,
                        lbl_80650218);
            effect_color_b = lbl_802FC5BC[5];
            fn_800EBA80(0, &point9, &effect_color_b, 100,
                        lbl_8065021C);
            fn_80226D28(1);
            final_color = lbl_802FC5BC[3];
            fn_801ECD74(&final_color);
        }
    }
}
