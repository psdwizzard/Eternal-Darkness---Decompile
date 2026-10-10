typedef unsigned char u8;
typedef unsigned int u32;

typedef struct GlobalState {
    u8 pad_00[8];
    int level;
} GlobalState;

typedef struct Entry8006D1DC {
    u8 pad_00[4];
    u8 minLevel;
    u8 pad_05[0x13];
    u32 flags;
} Entry8006D1DC;

extern GlobalState lbl_803003C8;
extern void *lbl_8064C4E0;
extern int lbl_8064CBC0;
extern int lbl_8064B820;
extern int lbl_8064D18C;

extern Entry8006D1DC *fn_8006D1DC(int id);
extern void *fn_80201814(void *);
extern int fn_801E79FC(void *, int);
extern int fn_80071900(void *);
extern int fn_8006B96C(int, int);
extern int fn_800AF6D4(void);

int fn_80071AD4(int id, u8 level, void *obj)
{
    Entry8006D1DC *entry;
    int result = 0;
    int bits = 0;

    if (id >= 0 && id <= 0x27) {
        entry = fn_8006D1DC(id);
        obj = fn_80201814(obj);
        if (entry->minLevel <= level) {
            result = 1;
        }

        switch (id) {
        case 15:
        case 22:
            result = 1;
            break;
        case 9:
            if (lbl_803003C8.level == 4 || lbl_803003C8.level == 3 ||
                lbl_803003C8.level == 1) {
                result = 0;
            }
            break;
        case 12:
            if (lbl_803003C8.level != 0) {
                if (fn_801E79FC(lbl_8064C4E0, 0x3bf)) {
                    result = 0;
                } else {
                    result = 1;
                }
            } else {
                result = 0;
            }
            break;
        case 27:
            if (lbl_803003C8.level < 5 && lbl_8064CBC0 == 0) {
                result = 0;
            }
            break;
        case 11:
        case 17:
            if (lbl_8064B820 == 0) {
                result = 0;
            }
            break;
        case 13:
            switch (lbl_803003C8.level) {
            case 0:
            case 5:
            case 7:
            case 9:
            case 10:
                if (lbl_803003C8.level == 0) {
                    if (fn_801E79FC(lbl_8064C4E0, 0x463)) {
                        result = 0;
                    }
                } else {
                    if (fn_801E79FC(lbl_8064C4E0, 0x464)) {
                        result = 0;
                    }
                }
                if (lbl_8064CBC0 != 0) {
                    result = 1;
                }
                break;
            default:
                result = 0;
                break;
            }
            break;
        }

        if (obj != 0 && fn_80071900(obj)) {
            bits |= 1;
        }

        if ((entry->flags & 0x1000) && !(bits & 1)) {
            result = 0;
        }

        if (fn_8006B96C(lbl_8064D18C, 5) != -1) {
            result = 0;
        }

        if (fn_800AF6D4() && (id == 0x18 || id == 0x1f)) {
            result = 0;
        }

        switch (lbl_803003C8.level) {
        case 9:
            if (fn_801E79FC(lbl_8064C4E0, 0x206)) {
                result = 0;
            }
            break;
        case 13:
        case 15:
        case 16:
            result = 0;
            break;
        }
    }

    return result;
}
