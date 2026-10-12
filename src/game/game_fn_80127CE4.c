typedef struct ShortCoord3 {
    short x, y, z;
} ShortCoord3;

typedef struct Coord3 {
    float x, y, z;
} Coord3;

typedef struct PositionKey {
    unsigned int flags;
    ShortCoord3 value;
} PositionKey;

extern unsigned int fn_801285CC(const unsigned int* value);
extern void fn_8013530C(void);
extern void fn_801270DC(float* output, short* input);
extern void fn_8017974C(ShortCoord3* first, ShortCoord3* second,
                       Coord3* output, float amount);
extern const float lbl_80650198;
extern const float lbl_8065019C;
extern const float lbl_806501A0;

void fn_80127CE4(PositionKey* left, PositionKey* right, Coord3* output,
                 float amount)
{
    if ((int)fn_801285CC(&left->flags) != 1 ||
        (int)fn_801285CC(&right->flags) != 1) {
        fn_8013530C();
    }

    if (amount <= lbl_80650198) {
        fn_801270DC(&output->x, &left->value.x);
    } else if (lbl_8065019C - amount <= lbl_80650198) {
        fn_801270DC(&output->x, &right->value.x);
    } else if ((int)fn_801285CC(&left->flags) == 1 &&
               (int)fn_801285CC(&right->flags) == 1) {
        fn_8017974C(&left->value, &right->value, output, amount);
        output->x *= lbl_806501A0;
        output->y *= lbl_806501A0;
        output->z *= lbl_806501A0;
    }
}
