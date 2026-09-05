typedef signed short s16;
typedef unsigned char u8;
typedef float f32;

typedef struct FloatRow {
    f32 values[3];
} FloatRow;

extern s16 lbl_8023BA30[][5];
extern FloatRow lbl_80255790[];
extern f32 lbl_80651078;

f32 fn_801D1B7C(int arg0, int arg1, u8 arg2)
{
    FloatRow* values = lbl_80255790;
    f32 result = lbl_80651078;
    s16 value;

    if (arg0 == 0) {
        return result;
    }
    if (arg1 == 0) {
        return result;
    }
    if (arg1 == 4) {
        return result;
    }
    if (arg2 < 2) {
        return result;
    }
    if (arg2 > 4) {
        return result;
    }

    value = lbl_8023BA30[arg1][arg0];
    switch (value) {
    case -1: {
        return values[0].values[arg2 - 2];
    }
    case 1: {
        return values[1].values[arg2 - 2];
    }
    default: {
        return values[2].values[arg2 - 2];
    }
    }
}
