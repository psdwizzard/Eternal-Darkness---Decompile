typedef unsigned char u8;
typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;
extern const signed char lbl_80239D00[224];
extern void fn_800F86B4(decimal *, const signed char *, short);
extern void fn_800F87A0(decimal *, const decimal *, const decimal *);

void fn_800F8374(decimal *out, short exponent)
{
    decimal half;
    decimal original;
    decimal two;
    decimal one_half;
    short e = exponent;

    switch (e) {
    case -64: fn_800F86B4(out, lbl_80239D00 + 0x25, -20); break;
    case -53: fn_800F86B4(out, lbl_80239D00 + 0x53, -16); break;
    case -32: fn_800F86B4(out, lbl_80239D00 + 0x7A, -10); break;
    case -16: fn_800F86B4(out, lbl_80239D00 + 0x92, -5); break;
    case -8: fn_800F86B4(out, lbl_80239D00 + 0x9F, -3); break;
    case -7: fn_800F86B4(out, lbl_80239D00 + 0xA6, -3); break;
    case -6: fn_800F86B4(out, lbl_80239D00 + 0xAC, -2); break;
    case -5: fn_800F86B4(out, lbl_80239D00 + 0xB2, -2); break;
    case -4: fn_800F86B4(out, lbl_80239D00 + 0xB7, -2); break;
    case -3: fn_800F86B4(out, lbl_80239D00 + 0xBB, -1); break;
    case -2: fn_800F86B4(out, lbl_80239D00 + 0xBF, -1); break;
    case -1: fn_800F86B4(out, lbl_80239D00 + 0xC2, -1); break;
    case 0: fn_800F86B4(out, lbl_80239D00 + 0xC4, 0); break;
    case 1: fn_800F86B4(out, lbl_80239D00 + 0xC6, 0); break;
    case 2: fn_800F86B4(out, lbl_80239D00 + 0xC8, 0); break;
    case 3: fn_800F86B4(out, lbl_80239D00 + 0xCA, 0); break;
    case 4: fn_800F86B4(out, lbl_80239D00 + 0xCC, 1); break;
    case 5: fn_800F86B4(out, lbl_80239D00 + 0xCF, 1); break;
    case 6: fn_800F86B4(out, lbl_80239D00 + 0xD2, 1); break;
    case 7: fn_800F86B4(out, lbl_80239D00 + 0xD5, 2); break;
    case 8: fn_800F86B4(out, lbl_80239D00 + 0xD9, 2); break;
    default:
        fn_800F8374(&half, (short)(e / 2));
        fn_800F87A0(out, &half, &half);
        if (e & 1) {
            original = *out;
            if (e > 0) {
                fn_800F86B4(&two, lbl_80239D00 + 0xC6, 0);
                fn_800F87A0(out, &original, &two);
            } else {
                fn_800F86B4(&one_half, lbl_80239D00 + 0xC2, -1);
                fn_800F87A0(out, &original, &one_half);
            }
        }
        break;
    }
}
