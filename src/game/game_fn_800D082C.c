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
extern void *fn_80201814(void *);
extern State *fn_800A1D28(void *);
extern int fn_8003BD48(void *, void *);
extern int fn_80201B54(void *);
extern void *fn_801A74B8(void *);
extern void fn_800A37CC(int, void *, void *);
extern int fn_801A7468(void *);
extern void fn_8011F114(Vec3 *, void *);
extern int fn_8011F6A4(void *, int, int, int, Transform *, int);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern float fn_80211B08(Vec3 *);

/* Independent reconstruction of the object/context action callback. */
int fn_800D082C(void *object, void *context)
{
    /* Same-width address copies preserve MWCC's saved-register allocation. */
    register unsigned long context_saved = (unsigned long)context;
    register unsigned long object_saved = (unsigned long)object;
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

    owner = fn_80201814(fn_801A7498((void *)context_saved));
    state = fn_800A1D28(owner);
    if (state->timer == 0 && (fn_8003BD48((void *)object_saved, (void *)context_saved) & 3)) {
        id = fn_80201B54(owner);
        target = fn_801A74B8((void *)context_saved);
        state->timer = 210;
        fn_800A37CC(id, target, (void *)context_saved);
        kind = fn_801A7468((void *)context_saved);
        fn_8011F114(&initial, (void *)object_saved);
        position = initial;

        if (kind == 4 || kind == 6) {
            variant = 7;
        } else if (kind == 5 || kind == 7) {
            variant = 6;
        } else if (kind == 25) {
            variant = -1;
        }

        fn_8011F6A4((void *)object_saved, 2, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4((void *)object_saved, 3, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4((void *)object_saved, 28, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
        fn_8011F6A4((void *)object_saved, 29, variant, -1, &transformed, 1);
        fn_80211A6C(&position, &transformed.vector, &output);
        fn_80211B08(&output);
    }
    return 1;
}
