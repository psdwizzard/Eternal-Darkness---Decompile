typedef unsigned char u8;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    u8 pad_00[0x1B4];
    void *handle;
} State;

extern void fn_8011F114();
extern void PSVECSubtract();
extern float PSVECSquareMag(const Vec3 *);
extern void *fn_80137FB8(void *);
extern void fn_8012B7D0(void *, Vec3 *);
extern void fn_8017AB08(const Vec3 *, Vec3 *);
extern void PSVECAdd(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);
extern void PSVECScale(const Vec3 *, Vec3 *, float);
extern Vec3 lbl_80239194;
extern const float lbl_8064E894;
extern const float lbl_8064E898;

int fn_80074580(void *object, void *other, Vec3 *position, State *state,
                Vec3 *result)
{
    register void *other_r = other;
    register Vec3 *position_r = position;
    register State *state_r = state;
    register Vec3 *result_r = result;
    register int found;
    Vec3 other_position;
    Vec3 direction;
    Vec3 scaled;
    Vec3 constant = lbl_80239194;
    Vec3 transformed;
    Vec3 object_position;
    Vec3 handle_position;
    void *handle;

    found = 0;
    fn_8011F114(&object_position, object);
    *position_r = object_position;
    fn_8011F114(&other_position, other_r);
    PSVECSubtract(&other_position, position_r, &direction);
    if (PSVECSquareMag(&direction) > lbl_8064E894) {
        handle = fn_80137FB8(state_r->handle);
        if (handle != 0) {
            handle_position = *(Vec3 *)handle;
            fn_8012B7D0(other_r, &handle_position);
            fn_8017AB08(&constant, &transformed);
            PSVECAdd(&other_position, &transformed, result_r);
        } else {
            PSVECNormalize(&direction, &scaled);
            PSVECScale(&scaled, &scaled, lbl_8064E898);
            PSVECAdd(&other_position, &scaled, result_r);
        }
        found = 1;
    } else {
        *result_r = other_position;
    }
    return found;
}
