typedef float Matrix34[3][4];

extern void PSMTXTrans(Matrix34, float, float, float);
extern void PSMTXRotRad(Matrix34, int, float);
extern void PSMTXConcat(Matrix34, Matrix34, Matrix34);
extern void GXLoadTexMtxImm(Matrix34, int, int);
extern int* fn_801EF2B0(void);
extern void fn_801EDEC4(int, int, int, int);

void fn_8018D2E0(float value)
{
    Matrix34 second;
    Matrix34 first;
    Matrix34 result;
    int* states;
    int index;
    float angle;
    float scale;

    angle = value;
    value = -0.5f;
    scale = value;
    PSMTXTrans(first, scale, scale, 0.0f);
    PSMTXRotRad(second, 0x5A, angle);
    PSMTXConcat(second, first, result);
    scale = 0.5f;
    PSMTXTrans(first, scale, scale, 0.0f);
    PSMTXConcat(first, result, second);
    GXLoadTexMtxImm(second, 0x1E, 1);

    states = fn_801EF2B0();
    for (index = 0; index < 8; index++) {
        if (states[index] == 0) {
            fn_801EDEC4(index, 1, 4, 0x1E);
            break;
        }
    }
    for (index = 0; index < 8; index++) {
        if (states[index] == 5) {
            fn_801EDEC4(index, 1, 4, 0x1E);
            break;
        }
    }
}
