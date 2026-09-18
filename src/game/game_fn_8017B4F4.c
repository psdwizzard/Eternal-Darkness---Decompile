extern int lbl_8064D20C;
extern float lbl_80650900;
extern float lbl_80650904;
extern float lbl_80650908;
extern float lbl_8065090C;
extern int fn_8017BB60(void);
extern int fn_8017BB98(void);
extern int fn_8021EB20(int);
extern int fn_8017B8AC(void);
extern int fn_8017B904(void);

float fn_8017B4F4(int index)
{
    float value;
    int elapsed;
    int base;

    switch (fn_8017BB60()) {
    case 1:
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / lbl_80650900;
        break;
    case 4:
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / lbl_80650900;
        break;
    case 6:
        value = fn_8017B8AC();
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / value;
        break;
    case 7:
        value = fn_8017B904();
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / value;
        break;
    case 5:
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / lbl_80650904;
        break;
    case 8:
        elapsed = fn_8021EB20(index);
        base = (&lbl_8064D20C)[index];
        value = ((float)elapsed - (float)base) / lbl_80650904;
        break;
    default:
        value = lbl_80650908;
        break;
    }

    if (fn_8017BB98() == 0) {
        value = lbl_8065090C;
    }
    if (value > lbl_80650908) {
        value = lbl_80650908;
    }
    if (value < lbl_8065090C) {
        value = lbl_8065090C;
    }
    return value;
}
