/* __sformatter: MSL scanf core (__sformatter). */

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

void* __va_arg(void* list, int type);
#define va_arg(ap, t) (*(t*)__va_arg(ap, 1))

typedef unsigned short wchar_t;

extern unsigned char __ctype_map[]; /* __ctype_map */
inline int isspace(int c)
{
    return __ctype_map[(unsigned char)c] & 0x06;
}

#define EOF -1

enum __ReadProcActions {
    __GetAChar,
    __UngetAChar,
    __TestForError
};

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

#define tst_char_map(map, ch) ((map)[(unsigned char)(ch) >> 3] & (1 << ((ch) & 7)))

typedef struct {
    unsigned char suppress_assignment;
    unsigned char field_width_specified;
    unsigned char argument_options;
    unsigned char conversion_char;
    int field_width;
    char_map char_set;
} scan_format;

#define bad_conversion 0xFF

typedef int (*ReadProcType)(void*, int, int);

const char* fn_800FCAD0(const char* format_string, scan_format* format); /* parse_format */
unsigned long long __strtoull(int base, int max_width, ReadProcType ReadProc, void* ReadProcArg,
                               int* chars_scanned, int* negative, int* overflow); /* __strtoull */
unsigned long __strtoul(int base, int max_width, ReadProcType ReadProc, void* ReadProcArg,
                          int* chars_scanned, int* negative, int* overflow); /* __strtoul */
long double __strtold(int max_width, ReadProcType ReadProc, void* ReadProcArg, int* chars_scanned,
                        int* overflow); /* __strtold */
int mbtowc(wchar_t* pwc, const signed char* s, unsigned long n); /* mbtowc */

int __sformatter(ReadProcType ReadProc, void* ReadProcArg, const char* format_str, va_list arg)
{
    int num_chars, chars_read, items_assigned, conversions;
    int base, negative, overflow;
    const char* format_ptr;
    int format_char;
    signed char c;
    scan_format format;
    long long_num;
    unsigned long u_long_num;
    long long long_long_num;
    unsigned long long u_long_long_num;
    char* arg_ptr;
    long double long_double_num;
    int rval;

    format_ptr = format_str;
    chars_read = 0;
    items_assigned = 0;
    conversions = 0;

    while ((format_char = (signed char)*format_ptr) != 0) {
        if (isspace(format_char)) {
            do {
                format_char = (signed char)*++format_ptr;
            } while (isspace(format_char));

            while (isspace(c = (*ReadProc)(ReadProcArg, 0, __GetAChar))) {
                ++chars_read;
            }

            (*ReadProc)(ReadProcArg, c, __UngetAChar);
            continue;
        }

        if (format_char != '%') {
            if ((c = (*ReadProc)(ReadProcArg, 0, __GetAChar)) != (unsigned char)format_char) {
                (*ReadProc)(ReadProcArg, c, __UngetAChar);
                goto exit;
            }
            chars_read++;
            format_ptr++;
            continue;
        }

        format_ptr = fn_800FCAD0(format_ptr, &format);

        if (!format.suppress_assignment && format.conversion_char != '%') {
            arg_ptr = va_arg(arg, char*);
        } else {
            arg_ptr = 0;
        }

        if (format.conversion_char != 'n' && (*ReadProc)(ReadProcArg, 0, __TestForError)) {
            goto exit;
        }

        switch (format.conversion_char) {
        case 'd':
            base = 10;
            goto signed_int;
        case 'i':
            base = 0;
        signed_int:
            if (format.argument_options == long_long_argument) {
                u_long_long_num = __strtoull(base, format.field_width, ReadProc, ReadProcArg,
                                              &num_chars, &negative, &overflow);
            }
            if (format.argument_options != long_long_argument) {
                u_long_num = __strtoul(base, format.field_width, ReadProc, ReadProcArg, &num_chars,
                                         &negative, &overflow);
            }

            if (!num_chars) {
                goto exit;
            }

            chars_read += num_chars;

            if (format.argument_options == long_long_argument) {
                long_long_num = (negative ? -u_long_long_num : u_long_long_num);
            } else {
                long_num = (negative ? -u_long_num : u_long_num);
            }

            if (arg_ptr) {
                switch (format.argument_options) {
                case normal_argument:
                    *(int*)arg_ptr = long_num;
                    break;
                case char_argument:
                    *(signed char*)arg_ptr = long_num;
                    break;
                case short_argument:
                    *(short*)arg_ptr = long_num;
                    break;
                case long_argument:
                    *(long*)arg_ptr = long_num;
                    break;
                case long_long_argument:
                    *(long long*)arg_ptr = long_long_num;
                    break;
                }
                items_assigned++;
            }

            conversions++;
            break;

        case 'o':
            base = 8;
            goto unsigned_int;
        case 'u':
            base = 10;
            goto unsigned_int;
        case 'x':
        case 'X':
            base = 16;
        unsigned_int:
            if (format.argument_options == long_long_argument) {
                u_long_long_num = __strtoull(base, format.field_width, ReadProc, ReadProcArg,
                                              &num_chars, &negative, &overflow);
            }
            if (format.argument_options != long_long_argument) {
                u_long_num = __strtoul(base, format.field_width, ReadProc, ReadProcArg, &num_chars,
                                         &negative, &overflow);
            }

            if (!num_chars) {
                goto exit;
            }

            chars_read += num_chars;

            if (negative) {
                if (format.argument_options == long_long_argument) {
                    u_long_long_num = -u_long_long_num;
                } else {
                    u_long_num = -u_long_num;
                }
            }

            if (arg_ptr) {
                switch (format.argument_options) {
                case normal_argument:
                    *(unsigned int*)arg_ptr = u_long_num;
                    break;
                case char_argument:
                    *(unsigned char*)arg_ptr = u_long_num;
                    break;
                case short_argument:
                    *(unsigned short*)arg_ptr = u_long_num;
                    break;
                case long_argument:
                    *(unsigned long*)arg_ptr = u_long_num;
                    break;
                case long_long_argument:
                    *(unsigned long long*)arg_ptr = u_long_long_num;
                    break;
                }
                items_assigned++;
            }

            conversions++;
            break;

        case 'a':
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            long_double_num = __strtold(format.field_width, ReadProc, ReadProcArg, &num_chars, &overflow);

            if (!num_chars) {
                goto exit;
            }

            chars_read += num_chars;

            if (arg_ptr) {
                switch (format.argument_options) {
                case normal_argument:
                    *(float*)arg_ptr = long_double_num;
                    break;
                case double_argument:
                    *(double*)arg_ptr = long_double_num;
                    break;
                case long_double_argument:
                    *(long double*)arg_ptr = long_double_num;
                    break;
                }
                items_assigned++;
            }

            conversions++;
            break;

        case 'c':
            if (!format.field_width_specified) {
                format.field_width = 1;
            }

            if (arg_ptr) {
                num_chars = 0;

                while (format.field_width-- && (rval = (*ReadProc)(ReadProcArg, 0, __GetAChar)) != EOF) {
                    c = rval;
                    if (format.argument_options == wchar_argument) {
                        mbtowc((wchar_t*)arg_ptr, &c, 1);
                        arg_ptr++;
                    } else {
                        *arg_ptr++ = c;
                    }
                    num_chars++;
                }

                if (!num_chars) {
                    goto exit;
                }

                chars_read += num_chars;
                items_assigned++;
            } else {
                num_chars = 0;

                while (format.field_width-- && (c = (*ReadProc)(ReadProcArg, 0, __GetAChar)) != EOF) {
                    num_chars++;
                }

                if (!num_chars) {
                    goto exit;
                }
            }

            conversions++;
            break;

        case '%':
            while (isspace(c = (*ReadProc)(ReadProcArg, 0, __GetAChar))) {
                chars_read++;
            }

            if (c != '%') {
                (*ReadProc)(ReadProcArg, c, __UngetAChar);
                goto exit;
            }

            chars_read++;
            break;

        case 's':
            c = (*ReadProc)(ReadProcArg, 0, __GetAChar);
            while (isspace(c)) {
                chars_read++;
                c = (*ReadProc)(ReadProcArg, 0, __GetAChar);
            }

            (*ReadProc)(ReadProcArg, c, __UngetAChar);

        case '[':
            if (arg_ptr) {
                num_chars = 0;

                while (format.field_width-- && (c = (*ReadProc)(ReadProcArg, 0, __GetAChar)) != EOF &&
                       tst_char_map(format.char_set, c)) {
                    if (format.argument_options == wchar_argument) {
                        mbtowc((wchar_t*)arg_ptr, &c, 1);
                        arg_ptr = (char*)((wchar_t*)arg_ptr + 1);
                    } else {
                        *arg_ptr++ = c;
                    }
                    num_chars++;
                }

                if (!num_chars) {
                    (*ReadProc)(ReadProcArg, c, __UngetAChar);
                    goto exit;
                }

                chars_read += num_chars;

                if (format.argument_options == wchar_argument) {
                    *(wchar_t*)arg_ptr = 0;
                } else {
                    *arg_ptr = 0;
                }

                items_assigned++;
            } else {
                num_chars = 0;

                while (format.field_width-- && (c = (*ReadProc)(ReadProcArg, 0, __GetAChar)) != EOF &&
                       tst_char_map(format.char_set, c)) {
                    num_chars++;
                }

                if (!num_chars) {
                    (*ReadProc)(ReadProcArg, c, __UngetAChar);
                    goto exit;
                }

                chars_read += num_chars;
            }

            if (format.field_width >= 0) {
                (*ReadProc)(ReadProcArg, c, __UngetAChar);
            }

            conversions++;
            break;

        case 'n':
            if (arg_ptr) {
                switch (format.argument_options) {
                case normal_argument:
                    *(int*)arg_ptr = chars_read;
                    break;
                case short_argument:
                    *(short*)arg_ptr = chars_read;
                    break;
                case long_argument:
                    *(long*)arg_ptr = chars_read;
                    break;
                case char_argument:
                    *(char*)arg_ptr = chars_read;
                    break;
                case long_long_argument:
                    *(long long*)arg_ptr = chars_read;
                    break;
                }
            }
            continue;

        case bad_conversion:
        default:
            goto exit;
        }
    }

exit:
    if ((*ReadProc)(ReadProcArg, 0, __TestForError) && conversions == 0) {
        return EOF;
    }
    return items_assigned;
}
