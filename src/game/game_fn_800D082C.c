typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    u8 pad[0x284];
    short timer;
} State;

typedef struct Transform {
    u8 pad[8];
    Vec3 vector;
    u8 tail[16];
} Transform;

extern void* fn_801A7498(void *);
extern void *fn_80201814();
extern State *fn_800A1D28(void *);
extern int fn_8003BD48(void *, void *);
extern int fn_80201B54();
extern void *fn_801A74B8(void *);
extern void fn_800A37CC(int, void *, void *);
extern int fn_801A7468(void *);
extern void fn_8011F114();
extern int fn_8011F6A4(void *, int, int, int, Transform *, int);
extern void fn_80211A6C();
extern float fn_80211B08(Vec3 *);

/* Honest C reconstruction; callee-saved register allocation remains open. */
int fn_800D082C(void *object, void *context)
{
    int id;
    int kind;
    int variant;
    void *owner;
    State *state;
    void *target;
    Vec3 position;
    Vec3 output;
    Vec3 initial;
    Transform transformed;

    fn_801A7498(context);
    owner = fn_80201814();
    state = fn_800A1D28(owner);
    if (state->timer == 0 && (fn_8003BD48(object, context) & 3)) {
        id = fn_80201B54(owner);
        target = fn_801A74B8(context);
        state->timer = 210;
        fn_800A37CC(id, target, context);
        kind = fn_801A7468(context);
        fn_8011F114(&initial, object);
        position = initial;

        if (kind == 4 || kind == 6) {
            variant = 7;
        } else if (kind == 5 || kind == 7) {
            variant = 6;
        } else if (kind == 25) {
            variant = -1;
        }

        fn_8011F6A4(object, 2, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4(object, 3, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4(object, 28, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4(object, 29, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
    }
    return 1;
}
