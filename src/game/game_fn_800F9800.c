/* fn_800F9800: MSL is_utf8_complete (UTF-8 sequence length check for mbtowc) */

typedef unsigned long size_t;

int fn_800F9800(const char *s, size_t n) {
    /* MSL compiles this with signed chars; view the bytes that way */
    const signed char *b = (const signed char *)s;

    if (n == 0) {
        return -1;
    }
    if (*b == 0x00) {
        return 0;
    }
    if ((*b & 0x80) == 0x00) {
        return 1;
    } else if ((*b & 0xE0) == 0xC0) {
        if (n >= 2) {
            if ((*(b + 1) & 0x80) == 0x80) {
                return 2;
            }
            return -1;
        } else {
            return -2;
        }
    } else if ((*b & 0xF0) == 0xE0) {
        if (n >= 3) {
            if (((*(b + 1) & 0x80) == 0x80) && ((*(b + 2) & 0x80) == 0x80)) {
                return 3;
            }
            return -1;
        } else if ((n == 2 && ((*(b + 1) & 0x80) == 0x80)) || n == 1) {
            return -2;
        }
        return -1;
    }
    return -1;
}
