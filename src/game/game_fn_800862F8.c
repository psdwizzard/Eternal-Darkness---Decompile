/* Collision-limited beam effects for scene states 43, 74 and 89. */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef union Color {
    u32 word;
    struct { u8 r, g, b, a; } rgba;
} Color;

typedef struct ShortVec3 {
    short x, y, z;
} ShortVec3;

typedef struct Triangle {
    Vec3 a, b, c;
} Triangle;

typedef struct Beam {
    u8 pad0[0x14];
    Vec3 direction;
    Vec3 position;
    u8 pad2C[6];
    u8 active;
} Beam;

typedef struct BeamSlot {
    u8 pad0[0x6C];
    Beam *beam;
    u8 pad70[0x48];
} BeamSlot;

typedef struct GameState {
    u8 pad0[8];
    int first_blocked;
    int second_blocked;
    u8 pad10[9];
    u8 mode;
    u8 chain_active;
    u8 pad1B[0x33];
    u8 beams_active;
    u8 pad4F[0x13D];
    Vec3 start;
    Vec3 end;
    u8 pad1A4[0xC];
    Vec3 clipped;
    int beam_enabled;
} GameState;

typedef struct LevelState {
    u8 pad0[8];
    int phase;
} LevelState;

extern char lbl_80244870[];
extern GameState lbl_8031CBA0;
extern LevelState lbl_803003C8;
extern BeamSlot lbl_8031CD84[];
extern u32 *lbl_8064C4E0;
extern void *lbl_8064C4E4;
extern int lbl_8064D18C;
extern Color lbl_8064EB3C, lbl_8064EB40, lbl_8064EB44;
extern float lbl_8064EA08, lbl_8064EA14, lbl_8064EA78;
extern float lbl_8064EB48, lbl_8064EB4C, lbl_8064EB50;

extern void fn_80080A38(Vec3 *, const Vec3 *, Vec3 *, int, int);
extern void fn_800813D0(int, int);
extern void fn_80084404(void *, int, float);
extern int fn_8013638C(Vec3 *, Vec3 *, void *, Triangle *, float *, float);
extern void *fn_80158ABC(int, int, float *);
extern int fn_8015C4A4(void *, int);
extern u32 fn_80178E94(const float *, const float *);
extern u32 fn_801E741C(const char *);
extern int fn_801E79FC(u32 *, u32);
extern void fn_801FFE78(Vec3 *, Vec3 *, Vec3 *, u8, u32 *, u8,
                        float, float, float, float);
struct Entry80201814;
extern struct Entry80201814 *fn_80201814(int);
extern int fn_802019EC(int, int);
extern void *fn_80201BC8(void *);
extern void PSVECSubtract(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);

/* Load the two named points using the caller's point cursor. */
static inline void load_endpoints(Vec3 *output, ShortVec3 **source,
                                  int *resource, int *index)
{
    for (*index = 0; *index < 2; (*index)++) {
        source[*index] = fn_80158ABC(resource[*index], 2, 0);
        output[*index].x = source[*index]->x;
        output[*index].y = source[*index]->y;
        output[*index].z = source[*index]->z;
    }
}

/* The clipper can change its endpoint; each segment uses private copies. */
static inline void clip_segment(Vec3 *output, const Vec3 *input_start,
                                const Vec3 *input_end)
{
    Vec3 end;
    Vec3 start;
    Vec3 result;
    end = *input_end;
    start = *input_start;
    fn_80080A38(&result, &start, &end, 0, 1);
    *output = result;
}

static inline void clip_segment_to(Vec3 *result, const Vec3 *input_start,
                                   const Vec3 *input_end)
{
    Vec3 end;
    Vec3 start;
    end = *input_end;
    start = *input_start;
    fn_80080A38(result, &start, &end, 0, 1);
}

/* The renderer changes alpha, so give it a private color word. */
static inline void draw_segment(Vec3 *start, Vec3 *direction, Vec3 *end,
                                 Color color, u8 alpha,
                                 float start_radius, float end_radius)
{
    fn_801FFE78(start, direction, end, 16, &color.word, alpha,
                 start_radius, start_radius, end_radius, end_radius);
}

void fn_800862F8(void)
{
    /* The first element is the anchor; the other three are resource points. */
    Vec3 chain[4];
    Vec3 clipped[3];
    Triangle hit;
    Triangle chain_hit;
    Vec3 endpoints[2];
    Vec3 direction;
    int resources[3];
    Vec3 endpoint_direction;
    Vec3 beam_direction;
    Vec3 beam_end;
    int pair_resources[2];
    ShortVec3 *pair_points[2];
    Color chain_color;
    Color endpoint_color;
    float endpoint_fraction;
    Color beam_color;
    float beam_fraction;
    float initial_radius;
    float final_radius;
    int reset_index;
    BeamSlot *target_slot;
    u32 mask;
    char *names = lbl_80244870;
    /* Keep the first point handle alive while the chain iterator advances. */
    Vec3 *first_point[1];
    ShortVec3 *short_point;
    int point_index;
    Beam **source_controller;
    int endpoint_index;
    void *entry;
    int blocked;
    void *object;

    switch (lbl_8064D18C) {
    case 43:
        if (lbl_803003C8.phase != 11) {
            break;
        }
        chain_color = lbl_8064EB3C;
        if (!lbl_8031CBA0.beam_enabled) {
            break;
        }
        clip_segment(&lbl_8031CBA0.clipped, &lbl_8031CBA0.start,
                     &lbl_8031CBA0.end);
        PSVECSubtract(&lbl_8031CBA0.clipped, &lbl_8031CBA0.start, &direction);
        /* Preserve the order of the two radius reads. */
        initial_radius = *(volatile const float *)&lbl_8064EB48;
        final_radius = *(volatile const float *)&lbl_8064EA08;
        draw_segment(&lbl_8031CBA0.start, &direction, &lbl_8031CBA0.clipped,
                     chain_color, 100, initial_radius, final_radius);
        fn_800813D0(0, 1);
        if ((int)lbl_8031CBA0.mode != 2) {
            break;
        }
        resources[0] = fn_8015C4A4((void *)fn_801E741C(names + 0x70C), 2);
        resources[1] = fn_8015C4A4((void *)fn_801E741C(names + 0x718), 2);
        resources[2] = fn_8015C4A4((void *)fn_801E741C(names + 0x56C), 2);
        first_point[0] = &chain[1];
        for (point_index = 1; point_index < 4; point_index++) {
            short_point = fn_80158ABC(resources[point_index - 1], 2, 0);
            chain[point_index].x = short_point->x;
            chain[point_index].y = short_point->y;
            chain[point_index].z = short_point->z;
        }
        chain[0] = lbl_8031CBA0.clipped;
        clip_segment_to(&clipped[0], &chain[0], &chain[1]);
        PSVECSubtract(&clipped[0], &chain[0], &direction);
        draw_segment(&chain[0], &direction, &clipped[0], chain_color, 100,
                     lbl_8064EB4C, lbl_8064EB4C);
        if (lbl_8031CBA0.first_blocked != 0 ||
            fn_80178E94(&first_point[0]->x, &clipped[0].x) >= 30 ||
            !fn_801E79FC(lbl_8064C4E0, 0xD4)) {
            break;
        }
        clip_segment(&clipped[1], &chain[1], &chain[2]);
        PSVECSubtract(&clipped[1], first_point[0], &direction);
        draw_segment(first_point[0], &direction, &clipped[1], chain_color, 100,
                     lbl_8064EB4C, lbl_8064EB4C);
        if (lbl_8031CBA0.second_blocked != 0 ||
            fn_80178E94(&chain[2].x, &clipped[1].x) >= 30 ||
            !fn_801E79FC(lbl_8064C4E0, 0xD5)) {
            break;
        }
        clip_segment(&clipped[2], &chain[2], &chain[3]);
        if (fn_80178E94(&clipped[2].x, &chain[3].x) >= 30) {
            lbl_8031CBA0.chain_active = 0;
        }
        PSVECSubtract(&clipped[2], &chain[2], &direction);
        draw_segment(&chain[2], &direction, &clipped[2], chain_color, 100,
                     lbl_8064EB4C, lbl_8064EB4C);
        break;

    case 74:
        if (!fn_801E79FC(lbl_8064C4E0, 0x101)) {
            break;
        }
        endpoint_color = lbl_8064EB40;
        entry = fn_80201814(fn_802019EC(0x101, 74));
        pair_resources[0] = fn_8015C4A4((void *)fn_801E741C(names + 0x724), 2);
        pair_resources[1] = fn_8015C4A4((void *)fn_801E741C(names + 0x730), 2);
        load_endpoints(endpoints, pair_points, pair_resources, &endpoint_index);
        endpoint_direction.x = endpoints[1].x - endpoints[0].x;
        endpoint_direction.y = endpoints[1].y - endpoints[0].y;
        endpoint_direction.z = endpoints[1].z - endpoints[0].z;
        PSVECNormalize(&endpoint_direction, &endpoint_direction);
        if (entry != 0) {
            object = fn_80201BC8(entry);
            if (object != 0 && (mask = fn_8013638C(&endpoints[0], &endpoints[1],
                    object, &hit, &endpoint_fraction, lbl_8064EA78)) != 0U) {
                endpoints[1].x = endpoint_direction.x * endpoint_fraction +
                                 endpoints[0].x;
                endpoints[1].y = endpoint_direction.y * endpoint_fraction +
                                 endpoints[0].y;
                endpoints[1].z = endpoint_direction.z * endpoint_fraction +
                                 endpoints[0].z;
            }
        }
        draw_segment(&endpoints[0], &endpoint_direction, &endpoints[1],
                     endpoint_color, endpoint_color.rgba.a,
                     lbl_8064EB50, lbl_8064EB50);
        break;

    case 89: {
        Beam **target_controller;
        int link_index;

        if (lbl_803003C8.phase != 0) {
            break;
        }
        lbl_8031CBA0.beams_active = 1;
        for (reset_index = 1, target_slot = &lbl_8031CD84[1];
             reset_index < 4; reset_index++, target_slot++) {
            fn_80084404(&target_slot->beam, 0, lbl_8064EA14);
        }
        for (link_index = 1, target_slot = &lbl_8031CD84[1];
             link_index < 5; link_index++, target_slot++) {
            source_controller = &lbl_8031CD84[link_index - 1].beam;
            target_controller = &target_slot->beam;
            if (fn_801E79FC(lbl_8064C4E0, 0x13A) &&
                fn_801E79FC(lbl_8064C4E0, 0x13B) && (*source_controller)->active) {
                beam_color = lbl_8064EB44;
                beam_end = (*target_controller)->position;
                blocked = 0;
                if ((mask = fn_8013638C(&(*source_controller)->position,
                        &(*target_controller)->position, lbl_8064C4E4, &chain_hit, &beam_fraction, lbl_8064EA78)) != 0U) {
                    blocked = 1;
                    beam_end.x = (*source_controller)->direction.x * beam_fraction +
                                 (*source_controller)->position.x;
                    beam_end.y = (*source_controller)->direction.y * beam_fraction +
                                 (*source_controller)->position.y;
                    beam_end.z = (*source_controller)->direction.z * beam_fraction +
                                 (*source_controller)->position.z;
                }
                PSVECSubtract(&beam_end, &(*source_controller)->position, &beam_direction);
                draw_segment(&(*source_controller)->position, &beam_direction, &beam_end,
                             beam_color, beam_color.rgba.a,
                             lbl_8064EB4C, lbl_8064EB4C);
                if (blocked) {
                    break;
                }
            }
        }
        break;
    }
    }
}
