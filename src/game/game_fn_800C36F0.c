typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct PositionResult {
    u32 unknown[2];
    Vec3 position;
    Vec3 direction;
    u32 reserved[2];
} PositionResult;

extern int lbl_8064CA90;
extern float lbl_8064F1B8;
extern float lbl_8064F1BC;

extern int rand(void);
extern void *fn_8004910C(void *);
extern void *fn_801A7498(void *);
extern void *fn_80201814(void *);
extern void *fn_80201BC8(void *);
extern int fn_8011F6A4(void *, int, int, int, PositionResult *, int);
extern void fn_80152838(Vec3 *, Vec3 *, int);
extern int fn_801AC9F4(u16, int, Vec3 *, int);
extern void fn_80204028(void *, int, int, int);

int fn_800C36F0(void *unused, void *context)
{
    Vec3 start;
    Vec3 end;
    PositionResult location;
    int index;
    u16 sounds[11] = {0x2E, 0x2F, 0x30, 0x31, 0x32, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D};
    void *first;
    void *object;
    void *model;
    int sequence;
    float offset;

    index = rand() % 11;
    first = fn_8004910C(context);
    object = fn_80201814(fn_801A7498(context));
    model = fn_80201BC8(first);
    fn_8011F6A4(model, 3, 15, -1, &location, 1);

    sequence = lbl_8064CA90;
    start = location.position;
    end = start;
    lbl_8064CA90 = sequence + 1;
    if (sequence & 1) {
        goto odd;
    }
    offset = lbl_8064F1B8;
    goto selected;
odd:
    offset = lbl_8064F1BC;
selected:
    end.z += offset;
    fn_80152838(&start, &end, 4);
    fn_801AC9F4(sounds[index], 100, &start, 2);
    fn_80204028(object, 10000, 0, 0);
    return 0;
}
