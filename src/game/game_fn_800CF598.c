typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct RuntimeState {
    u8 pad0[0x9F];
    u8 kind;
} RuntimeState;

extern const Vec3f lbl_80239934;
extern const float lbl_8064F340;
extern int lbl_8064D18C;
extern void *fn_80201B8C(void *);
extern Vec3f *fn_80201BC8(void *);
extern void fn_8011F114(Vec3f *, Vec3f *);
extern void fn_801AAE68(int, int, int, Vec3f *, int, int, int, u16, int,
                       float);

void fn_800CF598(void *object)
{
    RuntimeState *state;
    int effect;
    Vec3f position;
    Vec3f *source;

    if (object == 0) {
        return;
    }
    state = ((RuntimeState *)fn_80201B8C(object));
    source = fn_80201BC8(object);
    position = lbl_80239934;
    effect = 622;
    if (source != 0) {
        fn_8011F114(&position, source);
    }
    switch (state->kind) {
    case 3:
    case 10:
    case 11:
    case 22:
    case 24:
    case 37:
    case 38:
    case 39:
    case 41:
        effect = 622;
        break;
    case 5:
        effect = 621;
        break;
    case 6:
        effect = 620;
        break;
    case 4:
        effect = 624;
        break;
    case 7:
        effect = 625;
        break;
    case 8:
        effect = 622;
        break;
    case 12:
        effect = 624;
        break;
    case 13:
        effect = 626;
        break;
    }
    fn_801AAE68(effect, 100, 0, &position, 2, 2, 0,
                (u16)lbl_8064D18C, 0, lbl_8064F340);
}
