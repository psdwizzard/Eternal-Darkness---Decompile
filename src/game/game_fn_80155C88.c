typedef signed char s8;

extern s8* fn_800FD40C(s8*, const s8*);
extern s8* strcat(s8*, const s8*);
extern s8 lbl_8064BA20[2];

void fn_80155C88(const s8* path, s8* output, const s8* extension)
{
    s8* cursor;
    s8* dot;

    dot = 0;
    cursor = output;
    fn_800FD40C(output, path);
    while (*cursor != 0) {
        switch (*cursor) {
        case '.':
            dot = cursor;
            break;
        case '\\':
            dot = 0;
            break;
        }
        cursor++;
    }
    if (dot != 0)
        *dot = 0;
    if (*extension != '.')
        strcat(output, lbl_8064BA20);
    strcat(output, extension);
}
