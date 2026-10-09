extern unsigned int fn_800F5C54(double value);
extern int fn_80130998(int kind, float scale);
extern float lbl_8065011C;
extern float lbl_80650120;

int fn_801234DC(int kind, register int use_first, float scale, register float value)
{
    register float saved_value;
    register int saved_use_first;
    int count;
    float multiplier;
    float converted;
    float scaled;
    int size;
    int result;

    /* ASM: fmr/mr retain the retail parameter-save order, which MWCC reverses for equivalent C assignments. */
    asm {
        fmr saved_value, value
        mr saved_use_first, use_first
    }
    count = fn_80130998(kind, scale);
    multiplier = lbl_8065011C;
    converted = (float)count;
    scaled = multiplier * converted;
    size = (fn_800F5C54(scaled) + 31) & ~31;
    result = size;

    if (saved_value < lbl_80650120 && saved_use_first != 0) {
        result = size * 3;
    }
    return size + result;
}
