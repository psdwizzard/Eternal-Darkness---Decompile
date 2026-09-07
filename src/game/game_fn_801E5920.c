typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FontInfo {
    int value;
} FontInfo;

extern u32 lbl_8064D580;
extern FontInfo* lbl_80633418[];
extern s8 lbl_80637628[];
extern s8* (*lbl_8064D58C)(s8*, int*);

extern int fn_801E41AC(s8*);
extern void fn_801E397C(s8*, s8*);
extern void fn_801E6F64(s8*, s8*);

void fn_801E5920(s8* text)
{
    int remaining;
    s8* cursor = text;
    int handled;

    while (*cursor != 0 || cursor[1] != 0) {
        remaining = 0;
        handled = 0;

        if (*cursor == '\\') {
            cursor++;
            if (*cursor == 'n') {
                cursor[-1] = '\n';
                fn_801E6F64(cursor, cursor + 1);
                handled = 1;
            } else {
                remaining = fn_801E41AC(cursor);
                cursor++;
            }
        }

        if (!handled) {
            do {
                if (*cursor == '~') {
                    s8* marker;
                    int limit;
                    s8 value;
                    int digits;

                    value = 0;
                    limit = 3;

                    if (lbl_80633418[lbl_8064D580]->value > 255)
                        limit = 5;

                    marker = cursor;
                    digits = 0;
                    cursor++;
                    while (*cursor >= '0' && *cursor <= '9' && digits < limit) {
                        value *= 10;
                        value += *cursor - '0';
                        digits++;
                        cursor++;
                    }
                    cursor = marker + 1;
                    if (digits != 0) {
                        *marker = value;
                        fn_801E6F64(cursor, cursor + digits);
                    } else {
                        fn_801E6F64(lbl_80637628, cursor + 1);
                        if (lbl_8064D58C != 0) {
                            int consumed;
                            s8* replacement = lbl_8064D58C(cursor, &consumed);
                            if (replacement != 0) {
                                fn_801E397C(marker, replacement);
                                cursor = marker + consumed;
                            }
                        }
                        fn_801E6F64(cursor, lbl_80637628);
                    }
                } else {
                    cursor++;
                }
                remaining--;
            } while (remaining > 0);
        }
    }
}
