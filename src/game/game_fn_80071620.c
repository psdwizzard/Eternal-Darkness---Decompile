typedef struct GlobalState {
    char pad_00[8];
    int level;
} GlobalState;

extern GlobalState lbl_803003C8;
extern volatile int *lbl_8064C5A8;
extern int fn_800CAC5C(int kind, int arg, int *outX, int *outY, int *outType);

typedef struct IntTriple {
    int values[3];
} IntTriple;

typedef struct IdList {
    int values[17];
} IdList;

typedef struct Tables {
    char pad[0x7C];
    IntTriple typesA;
    IntTriple xs;
    IntTriple ys;
    IdList ids;
} Tables;

extern const Tables lbl_802390A0;

int fn_80071620(int mode, int id, int event, int *outX, register int *outType, int *outY,
                unsigned char *flags)
{
    register const Tables *tables = &lbl_802390A0;
    IntTriple typesA;
    IntTriple xs;
    IntTriple ys;
    register int x2;
    register int y0;
    register int defaultType = 4;
    register int y2;
    register int y1;
    register int x1;
    register int x0;
    register int a2;
    register int a1;
    register int a0;
    int useDefault;
    int index;
    int *xTable;
    int *yTable;
    int result;

    result = 0;
    useDefault = 1;
    xTable = xs.values;
    yTable = ys.values;
    /* ASM: lwz captures the table values together; MWCC interleaves C copies
     * with their stores and reuses registers instead of retaining the snapshot. */
    asm {
        lwz a0, 0x7c(tables)
        lwz a1, 0x80(tables)
        lwz a2, 0x84(tables)
        lwz x0, 0x88(tables)
        lwz x1, 0x8c(tables)
    }
    /* ASM: lwz completes the same table snapshot before any local stores. */
    asm {
        lwz x2, 0x90(tables)
        lwz y0, 0x94(tables)
        lwz y1, 0x98(tables)
        lwz y2, 0x9c(tables)
    }
    typesA.values[0] = a0;
    typesA.values[1] = a1;
    typesA.values[2] = a2;
    xs.values[0] = x0;
    xs.values[1] = x1;
    xs.values[2] = x2;
    /* ASM: stw retains the early default-type value across the table loads;
     * a C store allows MWCC to rematerialize the constant after the loads. */
    asm {
        stw defaultType, 0(outType)
    }
    ys.values[0] = y0;
    ys.values[1] = y1;
    ys.values[2] = y2;

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
        xTable = typesA.values;
        break;
    case 0x13:
        useDefault = 0;
        if (mode == 0) {
            if (*flags & 2) {
                fn_800CAC5C(7, *lbl_8064C5A8, outX, outY, outType);
            } else if (*flags & 4) {
                fn_800CAC5C(5, 1, outX, outY, outType);
            } else {
                useDefault = 1;
            }
        } else if (mode == 1) {
            IdList ids = tables->ids;
            int notFound = 1;
            int i;

            for (i = 0; i < 17; i++) {
                if (id == ids.values[i]) {
                    notFound = 0;
                    break;
                }
            }
            if ((*flags & 1) && notFound) {
                fn_800CAC5C(4, *lbl_8064C5A8, outX, outY, outType);
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
