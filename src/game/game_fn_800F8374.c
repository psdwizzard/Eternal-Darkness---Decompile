typedef unsigned char u8;
typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;
extern const volatile char lbl_80239D00[224];
extern void *fn_800F86B4(decimal *, const volatile char *, int);
extern void fn_800F87A0(decimal *, const decimal *, const decimal *);

void fn_800F8374(decimal *out, short exponent)
{
    decimal half;
    decimal original;
    short e = exponent;

    switch (e) {
    case -64: fn_800F86B4(out, lbl_80239D00 + 0x25, -20); break;
    case -63: fn_800F86B4(out, lbl_80239D00 + 0x53, -16); break;
    case -62: fn_800F86B4(out, lbl_80239D00 + 0x7A, -10); break;
    case -61: fn_800F86B4(out, lbl_80239D00 + 0x92, -5); break;
    case -60: fn_800F86B4(out, lbl_80239D00 + 0x9F, -3); break;
    case -59: fn_800F86B4(out, lbl_80239D00 + 0xA6, -3); break;
    case -58: fn_800F86B4(out, lbl_80239D00 + 0xAC, -2); break;
    case -57: fn_800F86B4(out, lbl_80239D00 + 0xB2, -2); break;
    case -56: fn_800F86B4(out, lbl_80239D00 + 0xB7, -2); break;
    case -55: fn_800F86B4(out, lbl_80239D00 + 0xBB, -1); break;
    case -54: fn_800F86B4(out, lbl_80239D00 + 0xBF, -1); break;
    case -53: fn_800F86B4(out, lbl_80239D00 + 0xC2, -1); break;
    case -52: fn_800F86B4(out, lbl_80239D00 + 0xC4, 0); break;
    case -51: fn_800F86B4(out, lbl_80239D00 + 0xC6, 0); break;
    case -50: fn_800F86B4(out, lbl_80239D00 + 0xC8, 0); break;
    case -49: fn_800F86B4(out, lbl_80239D00 + 0xCA, 0); break;
    case -48: fn_800F86B4(out, lbl_80239D00 + 0xCC, 1); break;
    case -47: fn_800F86B4(out, lbl_80239D00 + 0xCF, 1); break;
    case -46: fn_800F86B4(out, lbl_80239D00 + 0xD2, 1); break;
    case -45: fn_800F86B4(out, lbl_80239D00 + 0xD5, 2); break;
    case -44: fn_800F86B4(out, lbl_80239D00 + 0xD9, 2); break;
    default:
        fn_800F8374(&half, (short)((e + (e < 0)) / 2));
        fn_800F87A0(out, &half, &half);
        if (e & 1) {
            original = *out;
            if (e > 0) {
                fn_800F86B4(&half, lbl_80239D00 + 0xC6, 0);
                fn_800F87A0(out, &original, &half);
            } else {
                fn_800F86B4(&half, lbl_80239D00 + 0xC2, -1);
                fn_800F87A0(out, &original, &half);
            }
        }
        break;
    }
}
