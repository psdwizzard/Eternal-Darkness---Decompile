/* fn_800FCAD0: MSL scanf parse_format. */

extern unsigned char lbl_8024AB90[]; /* __ctype_map */
#define isdigit(c) (lbl_8024AB90[(unsigned char)(c)] & 0x10)

#define INT_MAX 2147483647

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    long_long_argument,
    double_argument,
    long_double_argument,
    wchar_argument
};

typedef unsigned char char_map[32];

#define set_char_map(map, ch) map[(unsigned char)(ch) >> 3] |= (1 << ((ch) & 7))

typedef struct {
    unsigned char suppress_assignment;
    unsigned char field_width_specified;
    unsigned char argument_options;
    unsigned char conversion_char;
    int field_width;
    char_map char_set;
} scan_format;

#define bad_conversion 0xFF

const char* fn_800FCAD0(const char* format_string, scan_format* format)
{
    const signed char* s = (const signed char*)format_string;
    int c;
    int flag_found, invert;
    scan_format f = { 0, 0, normal_argument, 0, INT_MAX, { 0 } };

    if ((c = *++s) == '%') {
        f.conversion_char = c;
        *format = f;
        return (const char*)s + 1;
    }

    if (c == '*') {
        f.suppress_assignment = 1;
        c = *++s;
    }

    if (isdigit(c)) {
        f.field_width = 0;
        do {
            f.field_width = (f.field_width * 10) + (c - '0');
            c = *++s;
        } while (isdigit(c));

        if (f.field_width == 0) {
            f.conversion_char = bad_conversion;
            *format = f;
            return (const char*)s + 1;
        }
        f.field_width_specified = 1;
    }

    flag_found = 1;

    switch (c) {
    case 'h':
        f.argument_options = short_argument;
        if (s[1] == 'h') {
            f.argument_options = char_argument;
            c = *++s;
        }
        break;
    case 'l':
        f.argument_options = long_argument;
        if (s[1] == 'l') {
            f.argument_options = long_long_argument;
            c = *++s;
        }
        break;
    case 'L':
        f.argument_options = long_double_argument;
        break;
    default:
        flag_found = 0;
    }

    if (flag_found)
        c = *++s;

    f.conversion_char = c;

    switch (c) {
    case 'd':
    case 'i':
    case 'u':
    case 'o':
    case 'x':
    case 'X':
        if (f.argument_options == long_double_argument) {
            f.conversion_char = bad_conversion;
            break;
        }
        break;

    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
        if (f.argument_options == char_argument || f.argument_options == short_argument
            || f.argument_options == long_long_argument) {
            f.conversion_char = bad_conversion;
            break;
        }
        if (f.argument_options == long_argument)
            f.argument_options = double_argument;
        break;

    case 'p':
        f.argument_options = long_argument;
        f.conversion_char = 'x';
        break;

    case 'c':
        if (f.argument_options == long_argument)
            f.argument_options = wchar_argument;
        else if (f.argument_options != normal_argument)
            f.conversion_char = bad_conversion;
        break;

    case 's':
        if (f.argument_options == long_argument)
            f.argument_options = wchar_argument;
        else if (f.argument_options != normal_argument)
            f.conversion_char = bad_conversion;
        {
            int i;
            unsigned char* p;

            for (i = sizeof(f.char_set), p = f.char_set; i; --i)
                *p++ = 0xFF;

            f.char_set[1] = 0xC1;
            f.char_set[4] = 0xFE;
        }
        break;

    case '[':
        if (f.argument_options == long_argument)
            f.argument_options = wchar_argument;
        else if (f.argument_options != normal_argument)
            f.conversion_char = bad_conversion;

        c = *++s;
        invert = 0;

        if (c == '^') {
            invert = 1;
            c = *++s;
        }

        if (c == ']') {
            set_char_map(f.char_set, ']');
            c = *++s;
        }

        while (c && c != ']') {
            int d;

            set_char_map(f.char_set, c);

            if (*(s + 1) == '-' && (d = *(s + 2)) != 0 && d != ']') {
                while (++c <= d)
                    set_char_map(f.char_set, c);
                c = *(s += 3);
            } else
                c = *++s;
        }

        if (!c) {
            f.conversion_char = bad_conversion;
            break;
        }

        if (invert) {
            int i;
            unsigned char* p;

            for (i = sizeof(f.char_set), p = f.char_set; i; --i, ++p)
                *p = ~*p;
            break;
        }
        break;

    case 'n':
        break;

    default:
        f.conversion_char = bad_conversion;
        break;
    }

    *format = f;
    return (const char*)s + 1;
}
