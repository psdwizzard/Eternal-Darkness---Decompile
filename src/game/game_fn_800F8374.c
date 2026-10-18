typedef unsigned char u8;
typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;
extern const signed char lbl_80239D00[224];
extern void __str2dec(decimal *, const signed char *, short);
extern void __timesdec(decimal *, const decimal *, const decimal *);

void __two_exp(decimal *out, short exponent)
{
    decimal half;
    decimal original;
    decimal two;
    decimal one_half;
    short e = exponent;

    switch (e) {
    case -64: __str2dec(out, lbl_80239D00 + 0x25, -20); break;
    case -53: __str2dec(out, lbl_80239D00 + 0x53, -16); break;
    case -32: __str2dec(out, lbl_80239D00 + 0x7A, -10); break;
    case -16: __str2dec(out, lbl_80239D00 + 0x92, -5); break;
    case -8: __str2dec(out, lbl_80239D00 + 0x9F, -3); break;
    case -7: __str2dec(out, lbl_80239D00 + 0xA6, -3); break;
    case -6: __str2dec(out, lbl_80239D00 + 0xAC, -2); break;
    case -5: __str2dec(out, lbl_80239D00 + 0xB2, -2); break;
    case -4: __str2dec(out, lbl_80239D00 + 0xB7, -2); break;
    case -3: __str2dec(out, lbl_80239D00 + 0xBB, -1); break;
    case -2: __str2dec(out, lbl_80239D00 + 0xBF, -1); break;
    case -1: __str2dec(out, lbl_80239D00 + 0xC2, -1); break;
    case 0: __str2dec(out, lbl_80239D00 + 0xC4, 0); break;
    case 1: __str2dec(out, lbl_80239D00 + 0xC6, 0); break;
    case 2: __str2dec(out, lbl_80239D00 + 0xC8, 0); break;
    case 3: __str2dec(out, lbl_80239D00 + 0xCA, 0); break;
    case 4: __str2dec(out, lbl_80239D00 + 0xCC, 1); break;
    case 5: __str2dec(out, lbl_80239D00 + 0xCF, 1); break;
    case 6: __str2dec(out, lbl_80239D00 + 0xD2, 1); break;
    case 7: __str2dec(out, lbl_80239D00 + 0xD5, 2); break;
    case 8: __str2dec(out, lbl_80239D00 + 0xD9, 2); break;
    default:
        __two_exp(&half, (short)(e / 2));
        __timesdec(out, &half, &half);
        if (e & 1) {
            original = *out;
            if (e > 0) {
                __str2dec(&two, lbl_80239D00 + 0xC6, 0);
                __timesdec(out, &original, &two);
            } else {
                __str2dec(&one_half, lbl_80239D00 + 0xC2, -1);
                __timesdec(out, &original, &one_half);
            }
        }
        break;
    }
}
