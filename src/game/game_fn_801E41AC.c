typedef unsigned int u32;

extern float lbl_8064C314;
extern volatile u32 lbl_8064D57C;
extern float lbl_80651264;
extern char lbl_8064C324;
extern char lbl_80264684[];
extern char lbl_802647EC[];
extern char lbl_8026480C[];

extern int fn_800FBFD0(char*, char*, ...);
extern void fn_801E5AD0(signed char);
extern void fn_801E7DCC(char*, ...);

int fn_801E41AC(signed char* text)
{
    int consumed;
    int digits;
    float scale;

    switch (*text) {
    case 'i':
        digits = 0;
        text++;
        while (*text >= '0' && *text <= '9' && digits < 3) {
            digits++;
            text++;
        }
        return digits;
    case 'c':
        return 4;
    case 'j':
    {
        signed char justification = text[1];
        switch (justification) {
        case 'c':
        case 'l':
        case 'n':
        case 'r':
            fn_801E5AD0(justification);
            break;
        default:
            fn_801E7DCC(lbl_802647EC, justification);
            break;
        }
        return 1;
    }
    case 's':
        consumed = 0;
        if (fn_800FBFD0((char*)text + 1, &lbl_8064C324, &scale, &consumed) > 0) {
            if (scale < lbl_80651264) {
                lbl_8064C314 = scale;
                return consumed;
            }
            fn_801E7DCC(lbl_80264684, (double)scale);
        }
        return -1;
    case 'r':
        return 0;
    case 'a':
    case 'f':
        return 1;
    case '\\':
        lbl_8064D57C = 1;
    case 'p':
    case '~':
        return -1;
    default:
        fn_801E7DCC(lbl_8026480C);
        return -1;
    }
}
