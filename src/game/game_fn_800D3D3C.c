typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ActorState {
    u8 pad[0x284];
    s16 cooldown;
} ActorState;

typedef struct SearchResult {
    int second;
    int first;
    Vec3 position;
    Vec3 direction;
    float value;
} SearchResult;

extern u32 fn_801A7498(void *event);
extern u32 fn_801A74B8(void *event);
extern u32 fn_801A7468(void *event);
extern void *fn_80201814(int id);
extern void *fn_800A1D28(void);
extern int fn_8003BD48(void *object, void *event);
extern int fn_80201B54(int *object);
extern void fn_800A37CC(void *object, void *owner, void *event);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern int fn_8011F6A4(void *object, int first, int second, int previous,
                       void *result, int options);
extern void fn_80211A6C(const Vec3 *a, const Vec3 *b, Vec3 *result);
extern float fn_80211B08(Vec3 *vector);

int fn_800D3D3C(void *object_arg, void *event_arg)
{
    register u8 *event = event_arg;
    register Vec3 *object = object_arg;
    SearchResult query;
    Vec3 position;
    Vec3 difference;
    Vec3 temporary;
    register int selection;
    register void *owner = fn_80201814(fn_801A7498(event));
    register ActorState *actor = (ActorState *)fn_800A1D28();

    if (actor->cooldown == 0 && (fn_8003BD48(object, event) & 3)) {
        register int id = fn_80201B54(owner);
        u32 event_owner = fn_801A74B8(event);
        register int type;

        actor->cooldown = 210;
        fn_800A37CC((void *)id, (void *)event_owner, event);
        type = fn_801A7468(event);
        fn_8011F114(&temporary, object);
        position = temporary;

        /* Retail assigns selection only for these supported event types. */
        if (type == 4 || type == 6 || type == 8) {
            selection = 7;
        } else if (type == 5 || type == 7 || type == 9) {
            selection = 6;
        } else if (type == 25) {
            selection = -1;
        }

        fn_8011F6A4(object, 2, selection, -1, &query, 1);
        fn_80211A6C(&position, &query.position, &difference);
        fn_80211B08(&difference);
        fn_8011F6A4(object, 3, selection, -1, &query, 1);
        fn_80211A6C(&position, &query.position, &difference);
        fn_80211B08(&difference);
        fn_8011F6A4(object, 28, selection, -1, &query, 1);
        fn_80211A6C(&position, &query.position, &difference);
        fn_80211B08(&difference);
        fn_8011F6A4(object, 29, selection, -1, &query, 1);
        fn_80211A6C(&position, &query.position, &difference);
        fn_80211B08(&difference);
    }
    return 1;
}
