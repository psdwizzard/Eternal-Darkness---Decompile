typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RelatedObject {
    u8 pad_00[0x6C];
    int id;
} RelatedObject;

typedef struct ObjectData {
    u8 pad_00[0x8C];
    RelatedObject *related;
    u8 pad_90[0xA];
    short variant;
    u8 pad_9C[2];
    u8 category;
    u8 type;
} ObjectData;

typedef struct GlobalState {
    u8 pad_00[8];
    int level;
} GlobalState;

typedef struct Entry80201814 Entry80201814;
typedef struct Object80201EB8 Object80201EB8;
extern GlobalState lbl_803003C8;
extern u32 *lbl_8064C4E0;
extern int *lbl_8064C5A8;
extern void *fn_80201B9C(void);
extern int fn_80201EB8(Object80201EB8 *);
extern int fn_80201B4C(int *);
extern void *fn_80201BC8(void *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201BC0(void *);
extern Entry80201814 *fn_80201814(int);
extern int fn_801E79FC(u32 *, u32);
extern int fn_800CAC5C(int, int, int *, int *, int *);
extern void fn_8011FB54(void *, void *);

void fn_80071E00(int value)
{
    int first, second, third;
    int kind;
    void *object;
    ObjectData *data;
    RelatedObject *related;
    void *other;
    void *otherObject;
    int enabled;
    void *node = fn_80201B9C();

    if (value == 0xFC && lbl_803003C8.level == 5 &&
        fn_801E79FC(lbl_8064C4E0, 0x373)) {
        node = 0;
    }

    while (node != 0) {
        int nodeValue = fn_80201EB8(node);
        if (nodeValue == value) {
            kind = fn_80201B4C(node);
            object = fn_80201BC8(node);
            data = fn_80201B8C(node);
            related = data != 0 ? data->related : 0;
            switch (kind) {
            case 1:
                if (data != 0 && data->category == 2) {
                    switch (data->type) {
                    case 31:
                    case 32:
                    case 33:
                    case 35:
                    case 36:
                    case 40:
                        break;
                    case 4:
                    {
                        enabled = 1;
                        if (value == 0xFF && lbl_803003C8.level == 5 &&
                            fn_801E79FC(lbl_8064C4E0, 0x373) &&
                            lbl_8064C5A8 != 0 &&
                            fn_800CAC5C(4, *lbl_8064C5A8, &first, &second, &third) &&
                            data->variant != (short)second) {
                            enabled = 0;
                        }
                        if (enabled && related != 0) {
                            other = fn_80201814(related->id);
                            fn_8011FB54(object, (void *)10000);
                            if (other != 0) {
                                otherObject = fn_80201BC8(other);
                                if (otherObject != 0) {
                                    fn_8011FB54(otherObject, (void *)10000);
                                }
                            }
                        }
                        break;
                    }
                    default:
                        fn_8011FB54(object, (void *)10000);
                        break;
                    }
                }
                break;
            }
        }
        node = fn_80201BC0(node);
    }
}
