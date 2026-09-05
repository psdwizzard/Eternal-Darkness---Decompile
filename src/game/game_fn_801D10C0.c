typedef unsigned int u32;

typedef struct TableRow {
    u32 values[3];
} TableRow;

typedef struct TableBlock {
    TableRow rows[4];
} TableBlock;

extern TableBlock lbl_802555A0[];

u32 fn_801D10C0(u32 flags)
{
    u32 value = 0;
    u32 low;
    u32 high;

    switch (flags & 0xF) {
    case 1:
        low = 0;
        break;
    case 2:
        low = 1;
        break;
    case 4:
        low = 2;
        break;
    case 8:
        low = 3;
        break;
    }

    switch (flags & 0x70000) {
    case 0x10000:
        high = 0;
        break;
    case 0x20000:
        high = 1;
        break;
    case 0x40000:
        high = 2;
        break;
    }

    switch (flags & 0x1FF0) {
    case 0x300:
        value = lbl_802555A0[0].rows[low].values[high];
        break;
    case 0x1040:
        value = lbl_802555A0[1].rows[low].values[high];
        break;
    case 0x410:
        value = lbl_802555A0[2].rows[low].values[high];
        break;
    case 0x810:
        value = lbl_802555A0[3].rows[low].values[high];
        break;
    case 0x1010:
        value = lbl_802555A0[4].rows[low].values[high];
        break;
    case 0x480:
        value = lbl_802555A0[5].rows[low].values[high];
        break;
    case 0x500:
        value = lbl_802555A0[6].rows[low].values[high];
        break;
    case 0x820:
        value = lbl_802555A0[7].rows[low].values[high];
        break;
    case 0x440:
        value = lbl_802555A0[8].rows[low].values[high];
        break;
    case 0x420:
        value = lbl_802555A0[9].rows[low].values[high];
        break;
    }
    return value;
}
