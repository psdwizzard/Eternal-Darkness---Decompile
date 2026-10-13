/* MSL wctomb: encode one 16-bit wide character as UTF-8. */
typedef unsigned short wchar_t;

typedef struct UTF8Prefixes {
    unsigned char bytes[4];
} UTF8Prefixes;

extern const UTF8Prefixes lbl_8064F960;

int fn_800F961C(char *output, wchar_t character)
{
    const UTF8Prefixes prefixes = lbl_8064F960;
    int count;
    char *end;

    if (!output) {
        return 0;
    }
    if (character < 0x80) {
        count = 1;
    } else if (character < 0x800) {
        count = 2;
    } else {
        count = 3;
    }

    end = output + count;
    switch (count) {
    case 3:
        *--end = (character & 0x3F) | 0x80;
        character >>= 6;
        /* fall through */
    case 2:
        *--end = (character & 0x3F) | 0x80;
        character >>= 6;
        /* fall through */
    case 1:
        *--end = character | prefixes.bytes[count];
    }
    return count;
}
