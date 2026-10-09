typedef struct GlobalState {
    char pad_00[8];
    int level;
} GlobalState;

extern GlobalState lbl_803003C8;
extern int *lbl_8064C5A8;
extern void fn_800CAC5C(int kind, int arg, int *outX, int *outY);

int fn_80071620(int mode, int id, int event, int *outX, int *outType, int *outY,
                unsigned char *flags)
{
    int typesA[3] = {0x41, 0x42, 0x40};
    int xs[3] = {0x16, 0x14, 0x0D};
    int ys[3] = {0x06, 0x07, 0x01};
    int *xTable;
    int *yTable;
    int useDefault;
    int index;
    int result;

    result = 0;
    useDefault = 1;
    xTable = xs;
    yTable = ys;
    *outType = 4;

    switch (lbl_8064C5A8[0]) {
    case 2:
        index = 0;
        break;
    case 3:
        index = 1;
        break;
    default:
        index = 2;
        break;
    }

    switch (event) {
    case 0x15:
        *outType = 0x29;
        xTable = typesA;
        break;
    case 0x13:
        useDefault = 0;
        if (mode == 0) {
            if (*flags & 2) {
                fn_800CAC5C(7, *lbl_8064C5A8, outX, outY);
            } else if (*flags & 4) {
                fn_800CAC5C(5, 1, outX, outY);
            } else {
                useDefault = 1;
            }
        } else if (mode == 1) {
            int ids[17] = {
                0x0E, 0x29, 0x66, 0x69, 0x70, 0x86, 0xBB, 0xBF, 0xC4,
                0xDE, 0xE9, 0xF3, 0xF7, 0xFA, 0x12D, 0x12E, 0x139,
            };
            int notFound = 1;
            int i;

            for (i = 0; i < 17; i++) {
                if (id == ids[i]) {
                    notFound = 0;
                    break;
                }
            }
            if ((*flags & 1) && notFound) {
                fn_800CAC5C(4, *lbl_8064C5A8, outX, outY);
            } else {
                useDefault = 1;
            }
        } else {
            useDefault = 1;
        }
        result = 1;
        break;
    case 9:
        *outX = 0x79;
        *outY = 0xB9;
        *outType = 0x1E;
        result = 0;
        useDefault = 0;
        switch (lbl_803003C8.level) {
        case 5:
            *outX = 0x79;
            *outY = 0xB9;
            break;
        case 4:
        case 7:
        case 8:
            *outX = 0x78;
            *outY = 0xB2;
            break;
        case 6:
            *outX = 0x6E;
            *outY = 0xB1;
            break;
        case 0:
        case 9:
            *outX = 0x71;
            *outY = 0xA9;
            break;
        case 10:
            *outX = 0x75;
            *outY = 0xAF;
            break;
        case 2:
            *outX = 0x72;
            *outY = 0xAA;
            break;
        case 11:
            *outX = 0x77;
            *outY = 0xB0;
            break;
        }
        break;
    }

    if (useDefault) {
        *outX = xTable[index];
        *outY = yTable[index];
    }
    return result;
}
