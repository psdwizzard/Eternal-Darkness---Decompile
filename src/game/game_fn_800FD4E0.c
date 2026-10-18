/* __strtold: MSL __strtold - scan a floating point number (decimal,
 * hexadecimal, INF or NAN) through a character read callback. */

typedef struct decimal {
    char sign;
    char unused;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[36];
        unsigned char unused;
    } sig;
} decimal;

/* __ctype_map, __upper_map, __lconv */
extern unsigned char __ctype_map[];
extern unsigned char __upper_map[];
extern char* __lconv[];

/* __float_nan, __float_huge, __double_huge, __extended_min, __extended_max */
extern long __float_nan[];
extern long __float_huge[];
extern long __double_huge[];
extern long __extended_min[];
extern long __extended_max[];

/* 0.0 constants */
extern double lbl_8064F978;
extern double lbl_8064F980;

/* __dec2num */
double __dec2num(const decimal* d);

#define NAN_VAL (*(float*)__float_nan)
#define INFINITY_VAL (*(float*)__float_huge)
#define HUGE_VAL_D (*(double*)__double_huge)
#define LDBL_MIN_D (*(double*)__extended_min)
#define LDBL_MAX_D (*(double*)__extended_max)

#define EOF (-1)
#define SHRT_MIN (-0x8000)
#define SHRT_MAX 0x7FFF
#define SIGDIGLEN 20

#define isspace(c) (__ctype_map[(unsigned char)(c)] & 0x06)
#define isdigit(c) (__ctype_map[(unsigned char)(c)] & 0x10)
#define isxdigit(c) (__ctype_map[(unsigned char)(c)] & 0x20)
#define isalpha(c) (__ctype_map[(unsigned char)(c)] & 0xC0)
static inline int toupper(int c) {
    return (c == EOF) ? EOF : (int)__upper_map[(unsigned char)c];
}

enum scan_states {
    start = 0x0001,
    sig_start = 0x0002,
    leading_sig_zeroes = 0x0004,
    int_digit_loop = 0x0008,
    frac_start = 0x0010,
    frac_digit_loop = 0x0020,
    sig_end = 0x0040,
    exp_start = 0x0080,
    leading_exp_digit = 0x0100,
    leading_exp_zeroes = 0x0200,
    exp_digit_loop = 0x0400,
    finished = 0x0800,
    failure = 0x1000,
    nan_state = 0x2000,
    infin_state = 0x4000,
    hex_state = 0x8000
};

enum hex_scan_states {
    not_hex = 0x0000,
    hex_start = 0x0001,
    hex_leading_sig_zeroes = 0x0002,
    hex_int_digit_loop = 0x0004,
    hex_frac_digit_loop = 0x0008,
    hex_sig_end = 0x0010,
    hex_exp_start = 0x0020,
    hex_leading_exp_digit = 0x0040,
    hex_leading_exp_zeroes = 0x0080,
    hex_exp_digit_loop = 0x0100
};

#define final_state(scan_state) (scan_state & (finished | failure))
#define success(scan_state) (scan_state & (leading_sig_zeroes | int_digit_loop | frac_digit_loop | \
                                           leading_exp_zeroes | exp_digit_loop | finished))

#define fetch() (count++, (*ReadProc)(ReadProcArg, 0, 0))
#define unfetch(c) (*ReadProc)(ReadProcArg, c, 1)

long double __strtold(int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg,
                        int* chars_scanned, int* overflow) {
    int scan_state = start;
    int hex_scan_state = not_hex;
    int count = 0;
    int spaces = 0;
    int c;
    decimal d = {0, 0, 0, {0, ""}};
    int sig_negative = 0;
    int exp_negative = 0;
    long exp_value = 0;
    int exp_adjust = 0;
    long double result;
    int sign_detected = 0;
    unsigned char* chptr = (unsigned char*)&result;
    unsigned char uch, uch1;
    int ui;
    int NibbleIndex;
    int expsign = 0;
    int exp_digits = 0;
    unsigned intdigits = 0;
    short hex_exp = 0;
    int radix_marker = *(unsigned char*)__lconv[0];

    *overflow = 0;
    c = fetch();

    while (count <= max_width && c != EOF && !final_state(scan_state)) {
        switch (scan_state) {
        case start:
            if (isspace(c)) {
                c = fetch();
                count--;
                spaces++;
                break;
            }

            switch (toupper(c)) {
            case '-':
                sig_negative = 1;
            case '+':
                c = fetch();
                sign_detected = 1;
                break;
            case 'I':
                c = fetch();
                scan_state = infin_state;
                break;
            case 'N':
                c = fetch();
                scan_state = nan_state;
                break;
            default:
                scan_state = sig_start;
                break;
            }
            break;

        case infin_state: {
            int i = 1;
            signed char model[] = "INFINITY";

            while (i < 8 && model[i] == toupper(c)) {
                i++;
                c = fetch();
            }

            if (i == 3 || i == 8) {
                if (sig_negative) {
                    result = -INFINITY_VAL;
                } else {
                    result = INFINITY_VAL;
                }
                *chars_scanned = spaces + i + sign_detected;
                return result;
            }
            scan_state = failure;
            break;
        }

        case nan_state: {
            int i = 1;
            int j = 0;
            signed char model[] = "NAN(";

            while (i < 4 && model[i] == toupper(c)) {
                i++;
                c = fetch();
            }

            if (i == 3 || i == 4) {
                if (i == 4) {
                    while (j < 32 && (isdigit(c) || isalpha(c))) {
                        j++;
                        c = fetch();
                    }
                    if (c != ')') {
                        scan_state = failure;
                        break;
                    }
                    j++;
                }
                if (sig_negative) {
                    result = -NAN_VAL;
                } else {
                    result = NAN_VAL;
                }
                *chars_scanned = spaces + i + j + sign_detected;
                return result;
            }
            scan_state = failure;
            break;
        }

        case sig_start:
            if (c == radix_marker) {
                scan_state = frac_start;
                c = fetch();
                break;
            }
            if (!isdigit(c)) {
                scan_state = failure;
                break;
            }
            if (c == '0') {
                c = fetch();
                if (toupper(c) == 'X') {
                    scan_state = hex_state;
                    hex_scan_state = hex_start;
                } else {
                    scan_state = leading_sig_zeroes;
                }
                break;
            }
            scan_state = int_digit_loop;
            break;

        case leading_sig_zeroes:
            if (c == '0') {
                c = fetch();
                break;
            }
            scan_state = int_digit_loop;
            break;

        case int_digit_loop:
            if (!isdigit(c)) {
                if (c == radix_marker) {
                    scan_state = frac_digit_loop;
                    c = fetch();
                } else {
                    scan_state = sig_end;
                }
                break;
            }
            if (d.sig.length < SIGDIGLEN) {
                d.sig.text[d.sig.length++] = c;
            } else {
                exp_adjust++;
            }
            c = fetch();
            break;

        case frac_start:
            if (!isdigit(c)) {
                scan_state = failure;
                break;
            }
            scan_state = frac_digit_loop;
            break;

        case frac_digit_loop:
            if (!isdigit(c)) {
                scan_state = sig_end;
                break;
            }
            if (d.sig.length < SIGDIGLEN) {
                if (c != '0' || d.sig.length) {
                    d.sig.text[d.sig.length++] = c;
                }
                exp_adjust--;
            }
            c = fetch();
            break;

        case sig_end:
            if (toupper(c) == 'E') {
                scan_state = exp_start;
                c = fetch();
                break;
            }
            scan_state = finished;
            break;

        case exp_start:
            if (c == '+') {
                c = fetch();
            } else if (c == '-') {
                c = fetch();
                exp_negative = 1;
            }
            scan_state = leading_exp_digit;
            break;

        case leading_exp_digit:
            if (!isdigit(c)) {
                scan_state = failure;
                break;
            }
            if (c == '0') {
                scan_state = leading_exp_zeroes;
                c = fetch();
                break;
            }
            scan_state = exp_digit_loop;
            break;

        case leading_exp_zeroes:
            if (c == '0') {
                c = fetch();
                break;
            }
            scan_state = exp_digit_loop;
            break;

        case exp_digit_loop:
            if (!isdigit(c)) {
                scan_state = finished;
                break;
            }
            exp_value = exp_value * 10 + (c - '0');
            if (exp_value > SHRT_MAX) {
                *overflow = 1;
            }
            c = fetch();
            break;

        case hex_state:
            switch (hex_scan_state) {
            case hex_start:
                chptr[0] = 0;
                chptr[1] = 0;
                chptr[2] = 0;
                chptr[3] = 0;
                chptr[4] = 0;
                chptr[5] = 0;
                chptr[6] = 0;
                chptr[7] = 0;
                NibbleIndex = 2;
                hex_scan_state = hex_leading_sig_zeroes;
                c = fetch();
                break;

            case hex_leading_sig_zeroes:
                if (c == '0') {
                    c = fetch();
                    break;
                }
                hex_scan_state = hex_int_digit_loop;
                break;

            case hex_int_digit_loop:
                if (!isxdigit(c)) {
                    if (c == radix_marker) {
                        hex_scan_state = hex_frac_digit_loop;
                        c = fetch();
                    } else {
                        hex_scan_state = hex_sig_end;
                    }
                    break;
                }
                if (NibbleIndex < 17) {
                    intdigits++;
                    uch = chptr[NibbleIndex / 2];
                    ui = toupper(c);
                    if (ui >= 'A') {
                        ui = ui - 'A' + 10;
                    } else {
                        ui -= '0';
                    }
                    uch1 = ui;
                    if (NibbleIndex % 2) {
                        uch |= uch1;
                    } else {
                        uch |= uch1 << 4;
                    }
                    chptr[NibbleIndex++ / 2] = uch;
                    c = fetch();
                } else {
                    c = fetch();
                }
                break;

            case hex_frac_digit_loop:
                if (!isxdigit(c)) {
                    hex_scan_state = hex_sig_end;
                    break;
                }
                if (NibbleIndex < 17) {
                    uch = chptr[NibbleIndex / 2];
                    ui = toupper(c);
                    if (ui >= 'A') {
                        ui = ui - 'A' + 10;
                    } else {
                        ui -= '0';
                    }
                    uch1 = ui;
                    if (NibbleIndex % 2) {
                        uch |= uch1;
                    } else {
                        uch |= uch1 << 4;
                    }
                    chptr[NibbleIndex++ / 2] = uch;
                    c = fetch();
                } else {
                    c = fetch();
                }
                break;

            case hex_sig_end:
                if (toupper(c) == 'P') {
                    hex_scan_state = hex_exp_start;
                    exp_digits++;
                    c = fetch();
                } else {
                    scan_state = finished;
                }
                break;

            case hex_exp_start:
                exp_digits++;
                if (c == '-') {
                    expsign = 1;
                } else if (c != '+') {
                    unfetch(c);
                    exp_digits--;
                }
                hex_scan_state = hex_leading_exp_digit;
                c = fetch();
                break;

            case hex_leading_exp_digit:
                if (!isdigit(c)) {
                    scan_state = failure;
                    break;
                }
                if (c == '0') {
                    hex_scan_state = hex_leading_exp_zeroes;
                    exp_digits++;
                    c = fetch();
                    break;
                }
                hex_scan_state = hex_exp_digit_loop;
                break;

            case hex_exp_digit_loop:
                if (!isdigit(c)) {
                    scan_state = finished;
                    break;
                }
                hex_exp = hex_exp * 10 + (c - '0');
                if (exp_value > SHRT_MAX) {
                    *overflow = 1;
                }
                exp_digits++;
                c = fetch();
                break;
            }
            break;
        }
    }

    if (!success(scan_state)) {
        *chars_scanned = 0;
    } else {
        count--;
        *chars_scanned = count + spaces;
    }

    unfetch(c);

    if (hex_scan_state == not_hex) {
        if (exp_negative) {
            exp_value = -exp_value;
        }

        {
            int n = d.sig.length;
            unsigned char* p = &d.sig.text[n];

            while (n-- && *--p == '0') {
                exp_adjust++;
            }

            d.sig.length = n + 1;
            if (d.sig.length == 0) {
                d.sig.text[d.sig.length++] = '0';
            }
        }

        exp_value += exp_adjust;
        if (exp_value < SHRT_MIN || exp_value > SHRT_MAX) {
            *overflow = 1;
        }

        if (*overflow) {
            if (exp_negative) {
                return lbl_8064F978;
            } else if (sig_negative) {
                return -HUGE_VAL_D;
            } else {
                return HUGE_VAL_D;
            }
        }

        d.exp = exp_value;
        result = __dec2num(&d);

        if (lbl_8064F978 != result && result < LDBL_MIN_D) {
            *overflow = 1;
        } else if (result > LDBL_MAX_D) {
            *overflow = 1;
            result = HUGE_VAL_D;
        }

        if (sig_negative && success(scan_state)) {
            result = -result;
        }
        return result;
    } else {
        unsigned long long* uptr = (unsigned long long*)&result;

        if (result != lbl_8064F980) {
            if (expsign) {
                hex_exp = -hex_exp;
            }

            while ((*(short*)&result & 0x00F0) != 0x0010) {
                *uptr >>= 1;
                hex_exp++;
            }

            hex_exp += 4 * (intdigits - 1);
            *(short*)&result &= 0x000F;
            *(short*)&result |= ((hex_exp + 1023) << 4);
            *chars_scanned = spaces + sign_detected + NibbleIndex + 1 + exp_digits;

            if (result != 0.0 && result < LDBL_MIN_D) {
                result = 0.0;
                *overflow = 1;
            } else if (result > LDBL_MAX_D) {
                *overflow = 1;
                result = HUGE_VAL_D;
            }

            if (sig_negative) {
                *(short*)&result |= 0x8000;
            }
        } else {
            result = lbl_8064F978;
        }
        return result;
    }
}
