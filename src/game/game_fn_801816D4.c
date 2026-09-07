typedef signed short s16;
typedef unsigned short u16;

extern s16 lbl_80606360[];
extern const float lbl_8065096C;
extern double lbl_80650970;
extern const float lbl_8065097C;
extern const float lbl_80650980;
extern const float lbl_80650984;
extern float fn_80048C2C(float);
extern float fn_80048C50(float);

void fn_801816D4(void)
{
    float angle;
    int i = 0;

    for (; i < 0x40; i++) {
        angle = lbl_8065096C * (lbl_8065097C * (float)(int)(u16)(i << 10) / lbl_80650980);
        lbl_80606360[i] = (s16)(lbl_80650984 * fn_80048C2C(angle));
        lbl_80606360[i + 0x40] = (s16)(lbl_80650984 * fn_80048C50(angle));
    }
}
