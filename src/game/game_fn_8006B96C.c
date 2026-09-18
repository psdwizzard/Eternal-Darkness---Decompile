typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

extern u8 lbl_80243EE8[];
extern s32 lbl_8064B52C;
extern u16 lbl_8064B530;
extern u16 lbl_8064B534;
extern void *lbl_8064C4E0;
extern s32 fn_801E79FC(void *, s32);

s32 fn_8006B96C(s32 event, s32 mode)
{
    u8 *base = lbl_80243EE8;
    s32 count = 0;
    s32 result = -1;
    s32 *requirements = 0;
    u16 *events = 0;
    s32 require_set = 1;
    s32 i;

    switch (mode) {
    case 9:
        switch (event) {
        case 0xA5:
        case 0xA9:
        case 0xEA:
        case 0x126:
        case 0x127:
            result = 0;
            break;
        case 0xA7:
        case 0xA8:
        case 0xE9:
        case 0x12B:
        case 0x12D:
        case 0x12E:
        case 0x132:
        case 0x133:
        case 0x134:
        case 0x139:
        case 0x142:
            result = 0;
            break;
        }
        break;
    case 4:
        switch (event) {
        case 0x54:
            if (fn_801E79FC(lbl_8064C4E0, 0x3F1) == 0) {
                result = 0;
            }
            break;
        case 0x44:
            if (fn_801E79FC(lbl_8064C4E0, 0x2A3) == 0) {
                result = 0;
            }
            break;
        default: {
            u16 *list = (u16 *)(base + 0x54);
            s32 *list_requirements = (s32 *)(base + 0x30);
            for (i = 0; i < 9; list++, i++) {
                if (event == *list) {
                    if (fn_801E79FC(lbl_8064C4E0, list_requirements[i]) != 0) {
                        result = i;
                    }
                    break;
                }
            }
            break;
        }
        }
        break;
    case 7:
        events = &lbl_8064B530;
        count = 1;
        requirements = &lbl_8064B52C;
        break;
    case 8:
        events = &lbl_8064B534;
        count = 1;
        break;
    case 6:
        events = (u16 *)(base + 0x80);
        requirements = (s32 *)(base + 0x68);
        count = 6;
        if (event == 0xCA) {
            require_set = 0;
        }
        break;
    case 3:
        switch (event) {
        case 0x68:
        case 0x9D:
        case 0xB9:
            result = 0;
            break;
        case 0x51:
            if (fn_801E79FC(lbl_8064C4E0, 0x2B3) == 0) {
                result = 0;
            }
            break;
        }
        break;
    case 1:
        events = (u16 *)(base + 0x00);
        count = 10;
        break;
    case 2:
        events = (u16 *)(base + 0x14);
        count = 5;
        break;
    case 5:
        events = (u16 *)(base + 0x20);
        count = 8;
        break;
    case 10:
        switch (event) {
        case 0x56:
            if (fn_801E79FC(lbl_8064C4E0, 0x202) == 0) {
                result = 0;
            }
            break;
        }
        break;
    }

    if (requirements != 0) {
        if (events != 0) {
            for (i = 0; i < count; events++, i++) {
                if (*events == event) {
                    if (require_set != 0) {
                        if (fn_801E79FC(lbl_8064C4E0, requirements[i]) == 0) {
                            result = i;
                        }
                    } else if (fn_801E79FC(lbl_8064C4E0, requirements[i]) != 0) {
                        result = i;
                    }
                    break;
                }
            }
        }
    } else if (events != 0) {
        for (i = 0; i < count; events++, i++) {
            if (*events == event) {
                result = i;
                break;
            }
        }
    }
    return result;
}
