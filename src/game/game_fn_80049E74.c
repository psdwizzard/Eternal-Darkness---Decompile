typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern int fn_8011EB14(u32 object);
extern short fn_80050A20();
extern short fn_800509DC();

extern void* lbl_8064C4E4;
extern int lbl_8064D5A8;
extern int lbl_8064B4C8;
extern int lbl_8064C838;

u16 fn_80049E74(u32 object, int mode, u8* out_level, u8* out_flags,
                u16* out_time)
{
    int type;
    short condition;
    u16 result = 0xFFFF;
    u16 time = 0;
    u8 level = 0;
    u8 flags = 0;
    u32 current = (u32)lbl_8064C4E4;
    int base = lbl_8064D5A8;

    if (object == current) {
        int next = 30;
        if (lbl_8064B4C8 == 30) {
            next = 31;
        }
        lbl_8064B4C8 = next;
        mode = next;
    }

    if (object == current && lbl_8064C838 > base - 10 &&
        lbl_8064C838 <= base) {
        flags = 8;
        goto done;
    }

    if (object == 0) {
        goto done;
    }

    type = fn_8011EB04(object);
    condition = fn_80050A20();

    if ((void*)object == lbl_8064C4E4) {
        lbl_8064C838 = base;
    }

    switch (type) {
    case 0:
    case 0x12:
    case 0x45:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x51:
    case 0x55:
    case 0x56:
    case 0x96:
        switch (mode) {
        case 30:
        case 32:
        case 52:
        case 81:
        {
            short value;
            value = fn_800509DC();
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 35;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                int scaled = (short)value * 10;
                result = 39;
                time = 1500;
                level = 50 - scaled / 3333;
            } else if ((short)value < 5000) {
                result = 37;
                level = 40;
                time = 1000;
            } else {
                result = 35;
                time = 300;
                level = 150000 / (short)value;
            }
            break;
        }
        case 31:
        case 82:
        {
            short value;
            value = fn_800509DC();
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 36;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                flags = 8;
            } else if ((short)value < 5000) {
                result = 38;
                level = 40;
                time = 1000;
            } else {
                result = 36;
                time = 300;
                level = 150000 / (short)value;
            }
            break;
        }
        }
        break;

    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x89:
        switch (mode) {
        case 30:
        case 32:
        case 52:
        case 81:
        {
            short value;
            value = -1;
            if (type != 0x89) {
                value = fn_800509DC();
            }
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 118;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                int scaled = (short)value * 10;
                result = 39;
                time = 1500;
                level = 50 - scaled / 3333;
            } else if ((short)value < 5000) {
                result = 120;
                level = 40;
                time = 1000;
            } else {
                result = 118;
                time = 600;
                level = 150000 / (short)value;
            }
            break;
        }
        case 31:
        case 82:
        {
            short value;
            value = fn_800509DC();
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 119;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                flags = 8;
            } else if ((short)value < 5000) {
                result = 121;
                level = 40;
                time = 1000;
            } else {
                result = 119;
                time = 600;
                level = 150000 / (short)value;
            }
            break;
        }
        }
        break;

    case 9:
    case 0x46:
        switch (mode) {
        case 30:
        case 32:
        case 52:
        case 81:
        {
            short value;
            value = fn_800509DC();
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 112;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                int scaled = (short)value * 10;
                result = 114;
                time = 1500;
                level = 50 - scaled / 3333;
            } else if ((short)value < 5000) {
                int scaled = (short)value * 30;
                result = 110;
                time = 1000;
                level = 80 - scaled / 5000;
            } else {
                result = 112;
                time = 600;
                level = 150000 / (short)value;
            }
            break;
        }
        case 31:
        case 82:
        {
            short value;
            value = fn_800509DC();
            flags = 4;
            if (condition != 0 && fn_8011EB14(object) != 5) {
                result = 113;
                level = 10;
                time = 100;
            } else if (fn_8011EB14(object) == 5) {
                flags = 8;
            } else if ((short)value < 5000) {
                int scaled = (short)value * 30;
                result = 111;
                time = 1000;
                level = 80 - scaled / 5000;
            } else {
                result = 113;
                time = 600;
                level = 150000 / (short)value;
            }
            break;
        }
        }
        break;

    case 0x8E:
        switch (mode) {
        case 30:
        case 32:
        case 52:
        case 81:
            flags = 4;
            result = 112;
            if (condition != 0) {
                level = 10;
                time = 100;
            } else {
                level = 15;
                time = 600;
            }
            break;
        case 31:
        case 82:
            flags = 4;
            result = 113;
            if (condition != 0) {
                level = 10;
                time = 100;
            } else {
                level = 15;
                time = 600;
            }
            break;
        }
        break;

    case 0x8F:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
        switch (mode) {
        case 30:
        case 32:
        case 52:
        case 81:
            flags = 4;
            result = 35;
            if (condition != 0) {
                level = 10;
                time = 100;
            } else {
                level = 15;
                time = 600;
            }
            break;
        case 31:
        case 82:
            flags = 4;
            result = 36;
            if (condition != 0) {
                level = 10;
                time = 100;
            } else {
                level = 15;
                time = 600;
            }
            break;
        }
        break;
    }

done:
    if (out_level != 0) {
        *out_level = level;
    }
    if (out_flags != 0) {
        *out_flags = flags;
    }
    if (out_time != 0) {
        *out_time = time;
    }
    return result;
}
