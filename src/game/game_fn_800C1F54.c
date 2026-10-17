typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Object Object;
typedef struct Object80201C24 Object80201C24;

typedef struct QueryResult {
    int index;
    int flags;
    float position[3];
    float direction[3];
    float value;
} QueryResult;

extern void *fn_8004910C();
extern void *fn_80201BC8(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void *fn_80201C24(Object80201C24 *);
extern int fn_80201AE4(void);
extern u16 fn_80158234(Object *);
extern u32 fn_801578AC(Object *);
extern u8 fn_80157A80(Object *);
extern void fn_80157A8C(Object *, u8);
extern int fn_8011EB04(Object *);
extern void fn_800CEA1C(int, int, void *, void *, int, u8, void *, float, float, float);
extern int fn_801ACB0C(u32, u32);
extern u32 lbl_802FC5BC[19];
extern float lbl_8064F110, lbl_8064F178, lbl_8064F17C;
extern float lbl_8064F180, lbl_8064F184, lbl_8064F188;
extern float lbl_8064F18C, lbl_8064F190, lbl_8064F194;

int fn_800C1F54(void *unused, void *event)
{
    QueryResult result;
    u16 kind;
    Object *source;
    void *entity;
    Object *state;
    float radius, scale;
    void *data;
    u32 owner;
    int mode;
    u8 i;
    u8 count;

    if (event != 0 && (entity = fn_8004910C(event)) != 0 &&
        (source = fn_80201BC8(entity)) != 0 &&
        fn_8011F6A4(source, 5, -1, -1, &result, 1) != -1 &&
        (state = fn_80201C24(entity)) != 0) {
        radius = lbl_8064F178;
        scale = lbl_8064F17C;
        data = &lbl_802FC5BC[13];
        owner = fn_80201AE4();
        mode = 0;
        kind = fn_80158234(state);
        fn_801578AC(state);
        count = fn_80157A80(state);
        fn_80157A8C(state, 0);
        switch (kind) {
        case 0x80:
            radius = lbl_8064F178;
            count = 1;
            break;
        case 1:
            radius = lbl_8064F180;
            data = &lbl_802FC5BC[6];
            if (fn_8011EB04(source) == 0x5F) {
                mode = 2;
            } else {
                count = 1;
            }
            break;
        case 8:
        case 0x10:
            scale = lbl_8064F184;
            break;
        case 0x20:
            radius = lbl_8064F188;
            mode = 2;
            scale = lbl_8064F18C;
            break;
        case 0x100:
            mode = 2;
            break;
        case 0x400:
            scale = lbl_8064F190;
            break;
        case 2:
            scale = lbl_8064F194;
            mode = 1;
            break;
        case 0x40:
            break;
        default:
            return 0;
        }
        fn_800CEA1C(0x8B, 1, result.position, result.direction, mode, count,
                     data, radius, lbl_8064F110, scale);
        for (i = 0; i < count; ++i) {
            fn_801ACB0C(0, owner);
        }
    }
    return 1;
}
