/* fn_800F96E0: MSL mbtowc (UTF-8 -> wchar_t) */

typedef unsigned short wchar_t;
typedef unsigned long size_t;

int fn_800F9800(const char *s, size_t n);

int fn_800F96E0(wchar_t *pwc, const char *s, size_t n) {
    wchar_t result_chr = 0;
    int number_of_bytes;
    int check_byte_count;
    const char *source_char;

    if (!s) {
        return 0;
    }
    if (!n) {
        return -1;
    }

    number_of_bytes = fn_800F9800(s, n);
    if (number_of_bytes < 0) {
        return -1;
    }

    source_char = s;
    switch (number_of_bytes) {
    case 3:
        result_chr |= (*source_char++ & 0x0F);
        result_chr <<= 6;
    case 2:
        result_chr |= (*source_char++ & 0x3F);
        result_chr <<= 6;
    case 1:
        result_chr |= (*source_char++ & 0x7F);
    }

    if (result_chr == 0) {
        check_byte_count = 0;
    } else if (result_chr < 0x80) {
        check_byte_count = 1;
    } else if (result_chr < 0x800) {
        check_byte_count = 2;
    } else {
        check_byte_count = 3;
    }

    if (check_byte_count != number_of_bytes) {
        return -1;
    }

    if (pwc) {
        *pwc = result_chr;
    }
    return number_of_bytes;
}
