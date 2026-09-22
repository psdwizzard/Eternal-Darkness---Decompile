typedef unsigned char u8;
typedef short s16;

extern float lbl_8063C0C8[];
extern s16 lbl_80607840[];
extern void fn_801252D8(int mode);
extern void fn_801A2AB4(float* matrix, void* input, s16* output, int count);

void fn_801A2BCC(u8* object, void* input, s16* output, int count)
{
    s16* transformed = lbl_80607840;
    int i;

    fn_801252D8(4);
    fn_801A2AB4(lbl_8063C0C8, input, lbl_80607840, count);

    for (i = 0; i < count; i++) {
        int z;
        int x;
        int bottom;
        int top;
        int right;
        int left;
        int y;
        int radius;

        radius = object[0x21];
        x = transformed[0];
        y = transformed[1];
        z = transformed[2];
        left = x - radius;
        top = y + radius;
        right = x + radius;
        bottom = y - radius;

        output[0] = left;
        output[1] = top;
        output[2] = z;
        output[3] = right;
        output[4] = top;
        output[5] = z;
        output[6] = right;
        output[7] = bottom;
        output[8] = z;
        output[9] = left;
        output[10] = bottom;
        output[11] = z;

        object += 0x38;
        transformed += 3;
        output += 12;
    }
}
