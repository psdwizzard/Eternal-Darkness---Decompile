typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SplineKey {
    int time;
    short first[3];
    short second[3];
    short third[3];
    short pad;
} SplineKey;

typedef struct LinearKey {
    int time;
    short position[3];
    short pad;
} LinearKey;

typedef struct MotionResource {
    unsigned char pad0[0x24];
    float speed;
    unsigned char pad28[0x38];
    unsigned short spline_count;
    unsigned short pad62;
    SplineKey* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    LinearKey* linear_keys;
} MotionResource;

typedef struct MotionState {
    Vec3 position;
    int time;
    int pad10;
    int key;
    int key_step;
    int time_step;
    int status;
    int sampler;
    float pad28;
    float pad2C;
    unsigned char pad30[0x30];
    void* transform;
    unsigned char pad64[0x10];
    struct MotionState* linked;
    float sample;
    MotionResource* resource;
    int pad80;
} MotionState;

extern void fn_801F800C(Vec3*, MotionState*);
extern void fn_801F8184(Vec3*, MotionState*);
extern float fn_801F89B4(Vec3*, Vec3*, MotionResource*);
extern float fn_801F8FAC(Vec3*, MotionResource*, float);
extern float fn_801F92F8(Vec3*, Vec3*, MotionResource*);
extern void fn_8017974C(short*, short*, Vec3*, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);
extern void fn_801F7218(MotionState*, float);
extern const float lbl_80651464;
extern const float lbl_80651478;
extern const float lbl_806514A0;

void fn_801F8264(MotionState* state)
{
    Vec3 base;
    Vec3 position;
    Vec3 animated;
    float amount;
    int next_key;
    MotionResource* resource;
    int finished;
    int key;
    int new_time;

    if (state->status == 5) {
        return;
    }

    fn_801F800C(&base, state);
    if (state->sampler == 1) {
        state->sample = fn_801F89B4(&base, &position, state->resource);
    } else if (state->sampler == 2) {
        state->sample = fn_801F8FAC(&position, state->resource, state->linked->sample);
    } else {
        state->sample = fn_801F92F8(&base, &position, state->resource);
    }

    if (state->status != 1 && state->status != 4) {
        if (state->transform != 0) {
            fn_801F8184(&position, state);
        }
        state->position = position;
    } else {
        new_time = state->time + state->time_step;
        finished = 0;
        key = state->key;
        next_key = key + state->key_step;
        resource = state->resource;
        state->time = new_time;
        if (resource->spline_count != 0) {
            SplineKey* current = &resource->spline_keys[key];
            SplineKey* next = &resource->spline_keys[next_key];
            amount = (float)(state->time - current->time) /
                     (float)(next->time - current->time);
            fn_80179814(current->first, next->first, current->second,
                        next->third, &animated, amount);
            if (amount >= lbl_80651478 || amount <= lbl_806514A0) {
                state->key = next_key;
            }
            if (state->key < 0 || state->key >= resource->spline_count) {
                finished = 1;
            }
        } else if (resource->linear_count != 0) {
            LinearKey* current = &resource->linear_keys[key];
            LinearKey* next = &resource->linear_keys[next_key];
            if (next->time == current->time) {
                amount = lbl_80651464;
            } else {
                amount = (float)(state->time - current->time) /
                         (float)(next->time - current->time);
            }
            fn_8017974C(current->position, next->position, &animated, amount);
            state->position = animated;
            if (amount >= lbl_80651478 || amount <= lbl_806514A0) {
                state->key = next_key;
            }
            if (state->key < 0 || state->key >= resource->linear_count) {
                finished = 1;
            }
        }
        if (finished) {
            state->time_step = 0;
            state->status = 4;
        }
        if (state->transform != 0) {
            fn_801F8184(&animated, state);
        }
        state->position = animated;
    }

    fn_801F7218(state, state->resource->speed);
}
