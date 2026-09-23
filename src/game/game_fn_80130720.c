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
extern float lbl_805AADC8[][3];
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

static void emit(Vec3* value)
{
    fn_80130984(value->x, value->y, value->z);
}

/* NonMatching: GC/1.3 folds the eight vertex addresses into component
 * load offsets and retains a reload of the second color staging slot. */
void fn_80130720(Object* object)
{
    Color first_source;
    Color first_color;
    Object* saved_object = object;
    Color second_color;
    Color third_color;
    Color fourth_color;
    Color effect_color_a;
    Color effect_color_b;
    Color final_color;
    volatile Color second_source;
    /* Keep the origin at vectors[-1]; indices below address the same array. */
    Vec3* vectors = &((Vec3*)lbl_805AADC8)[1];

    fn_80125ECC(saved_object);
    if (lbl_8064CF30 != 0) {
        if (saved_object == lbl_8064C4E4) {
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
            emit(&vectors[6]);
            emit(&vectors[7]);
            fn_80130980();

            second_color = (second_source = lbl_802FC5BC[7]);
            fn_801ECD74(&second_color);
            fn_80226AB4(168, 3, 2);
            emit(&vectors[2]);
            emit(&vectors[3]);
            fn_80130980();

            third_color = lbl_802FC5BC[8];
            fn_801ECD74(&third_color);
            fn_80226AB4(168, 3, 2);
            emit(&vectors[0]);
            emit(&vectors[1]);
            fn_80130980();

            fourth_color = lbl_802FC5BC[11];
            fn_801ECD74(&fourth_color);
            fn_80226AB4(168, 3, 2);
            emit(&vectors[4]);
            emit(&vectors[5]);
            fn_80130980();

            effect_color_a = lbl_802FC5BC[13];
            fn_800EBA80(0, &vectors[-1], &effect_color_a, 100,
                        lbl_80650218);
            effect_color_b = lbl_802FC5BC[5];
            fn_800EBA80(0, &vectors[8], &effect_color_b, 100,
                        lbl_8065021C);
            fn_80226D28(1);
            final_color = lbl_802FC5BC[3];
            fn_801ECD74(&final_color);
        }
    }
}
