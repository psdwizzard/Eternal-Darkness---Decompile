typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct QueryResult {
    u8 pad[8];
    Vec3 position;
    u8 tail[0x14];
} QueryResult;

typedef struct LookupPair {
    s32 first;
    s32 second;
} LookupPair;

typedef struct Context {
    u8 pad[0x94];
    s32 object_id;
} Context;

extern volatile s32 lbl_8064D18C;
extern s8 lbl_8064C590;
extern const float lbl_8064E5B8;
extern const float lbl_8064E5BC;
extern const LookupPair lbl_80243CE4[];
extern const LookupPair lbl_80243D24[];

extern int fn_80200C10(void *);
extern int fn_80200C38();
extern s32 fn_8015C4A4(s32 value, s32 kind);
extern Vec3s *fn_80158ABC(s32 value, s32 kind, void *extra);
extern void fn_8011F114();
extern s32 fn_8011F6A4(void *object, s32 first, s32 second, s32 index,
                       QueryResult *result, s32 mode);
extern void PSVECSubtract();
extern void PSVECNormalize(Vec3 *input, Vec3 *output);
extern void PSVECScale(Vec3 *input, Vec3 *output, float scale);
extern void PSVECAdd(Vec3 *left, Vec3 *right, Vec3 *output);
extern void fn_801AAE68(float intensity, s32 effect_type, s32 value, s32 arg3,
                        Vec3 *position, s32 arg5, s32 arg6, s32 arg7,
                        u16 owner, s32 arg9);
extern s32 fn_801D3A24(s32 object_id, s32 property);
extern void fn_8015295C(Vec3 *source, Vec3 *position, s32 type, s32 mode,
                        s32 source_kind);

void fn_8005EC6C(s32 owner, s32 unused, void *object, Context *context,
                 void *event)
{
    Vec3 direction;
    Vec3 position;
    QueryResult first;
    QueryResult second;
    s32 source_kind;

    if (owner != lbl_8064D18C) {
        return;
    }

    if (fn_80200C10(event) == 0xF5) {
        Vec3s *source = fn_80158ABC(fn_8015C4A4(fn_80200C38(event), 2), 2, 0);

        second.position.x = source->x;
        second.position.y = source->y;
        second.position.z = source->z;
        fn_8011F114(&direction, object);
        source_kind = 3;
    } else {
        s32 index = fn_80200C38(event);

        if (fn_8011F6A4(object, lbl_80243D24[index].second,
                        lbl_80243CE4[index].second, -1, &second, 1) != -1) {
            fn_8011F6A4(object, lbl_80243D24[index].first,
                        lbl_80243CE4[index].first, -1, &first, 1);
        }
        direction = first.position;
        source_kind = 2;
    }

    PSVECSubtract(&second.position, &direction, &position);
    PSVECNormalize(&position, &position);
    PSVECScale(&position, &position, lbl_8064E5B8);
    PSVECAdd(&second.position, &position, &direction);

    if (lbl_8064C590++ < 2) {
        fn_801AAE68(lbl_8064E5BC, 0x289, 0x5A, 0, &first.position, 2, 2, 0,
                    (u16)lbl_8064D18C, 0);
    }

    fn_8015295C(&second.position, &direction,
                fn_801D3A24(context->object_id, 0x31), 4, source_kind);
}
