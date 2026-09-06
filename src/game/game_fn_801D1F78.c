typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct ScreenPosition {
    s32 x;
    s32 y;
    s32 z;
} ScreenPosition;

typedef struct QueryResult {
    s32 words[2];
    Vec3 position;
    s32 tail[5];
} QueryResult;

typedef struct RingDefinition {
    u8 count;
    u8 pad;
    s16 radius;
    Vec3 center;
} RingDefinition;

typedef struct RingOutput {
    u8 pad[0x48];
    s32 rank[32];
} RingOutput;

extern volatile f32 lbl_8065107C;
extern f32 fn_80048C2C(f32);
extern f32 fn_80048C50(f32);
extern void fn_801F6B6C(Vec3*, ScreenPosition*, s32, s32);
extern void* fn_80201814(s32);
extern void* fn_80201BC8(void);
extern s32 fn_8011F6A4(void*, s32, s32, s32, QueryResult*, s32);

void fn_801D1F78(RingOutput* output_arg, volatile RingDefinition* ring_arg, s32 object_arg)
{
    s32 projected[9];
    s32 order[9];
    QueryResult query_a;
    QueryResult query_b;
    Vec3 point;
    ScreenPosition screen;
    Vec3 reference_a;
    Vec3 reference_b;
    ScreenPosition reference_a_screen;
    ScreenPosition reference_b_screen;
    u8 count;
    volatile RingDefinition* ring;
    f32 circle;
    s32* projected_ptr;
    RingOutput* output;
    s32 object;
    s32 i;
    s32 best_index;
    s32 best;
    s32 j;
    f32 angle;
    void* context;

    count = ring_arg->count;
    ring = ring_arg;
    circle = lbl_8065107C;
    projected_ptr = projected;
    output = output_arg;
    object = object_arg;

    for (i = 0; i < count; i++) {
        angle = circle * (f32)i / (f32)count;
        point.x = ring->center.x + (f32)ring->radius * fn_80048C2C(angle);
        point.y = ring->center.y + (f32)ring->radius * fn_80048C50(angle);
        point.z = ring->center.z;
        fn_801F6B6C(&point, &screen, 0, 0);
        *projected_ptr++ = screen.x;
    }

    for (i = 0; i < count; i++) {
        best = projected[0];
        best_index = 0;
        for (j = 1; j < count; j++) {
            if (projected[j] > best) {
                best_index = j;
                best = projected[j];
            }
        }
        order[i] = best_index;
        projected[best_index] = (s32)0x80000000;
    }

    fn_80201814(object);
    context = fn_80201BC8();
    fn_8011F6A4(context, 0x15, 0xF, -1, &query_a, 1);
    fn_8011F6A4(context, 0x16, 0xF, -1, &query_b, 1);

    reference_a.x = query_a.position.x;
    reference_a.y = query_a.position.y;
    reference_a.z = query_a.position.z;
    reference_b.x = query_b.position.x;
    reference_b.y = query_b.position.y;
    reference_b.z = query_b.position.z;
    fn_801F6B6C(&reference_a, &reference_a_screen, 0, 0);
    fn_801F6B6C(&reference_b, &reference_b_screen, 0, 0);

    if (reference_a_screen.x < reference_b_screen.x) {
        for (i = 0; i < count; i++) {
            output->rank[order[count - 1 - i]] = i;
        }
    } else {
        for (i = 0; i < count; i++) {
            output->rank[order[i]] = i;
        }
    }
}
