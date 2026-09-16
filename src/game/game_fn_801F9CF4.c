typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortVec3 {
    short x, y, z;
} ShortVec3;

typedef struct MotionResource {
    ShortVec3 base;
    unsigned char pad06[0x1E];
    float speed;
    unsigned char pad28[0x38];
    unsigned short spline_count;
    unsigned short pad62;
    void* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    void* linear_keys;
    unsigned char pad70[8];
} MotionResource;

typedef struct MotionState {
    Vec3 position;
    int time;
    int resource_index;
    int key;
    int direction_a;
    int direction_b;
    int mode;
    int interpolation_mode;
    float field28;
    float field2C;
    unsigned char pad30[4];
    float resource_speed;
    unsigned char pad38[0xC];
    int field44;
    unsigned char pad48[0x20];
    void* callback_object;
    void (*callback)(void);
    unsigned char pad70[4];
    struct MotionState* previous;
    float interpolated_time;
    MotionResource* resource;
    void (*endpoint_callback)(void);
} MotionState;

extern void* lbl_8064C4E4;
extern const float lbl_80651464;
extern short* fn_801F99C0(MotionResource*, int);
extern int fn_801F9A38(MotionResource*, int);
extern int fn_801F9AA8(MotionResource*, int);
extern void fn_801F800C(void*, MotionState*);
extern float fn_801F89B4(void*, Vec3*, MotionResource*);
extern float fn_801F8FAC(Vec3*, MotionResource*, float);
extern float fn_801F92F8(void*, Vec3*, MotionResource*);
extern void fn_801F8994(MotionState*, Vec3*, float);
extern void fn_801F8234(void);
extern void fn_801F8264(void);
extern void fn_801F7FBC(void);

void fn_801F9CF4(MotionState* state, int resource_index, int endpoint,
                 int reverse, int interpolation_mode, int use_callback,
                 MotionResource* resources)
{
    short* first;
    ShortVec3 fallback;
    unsigned char snapshot[0x10];
    Vec3 sample;
    Vec3 terminal_sample;

    state->mode = 3;
    if (resources[resource_index].linear_count != 0 ||
        resources[resource_index].spline_count != 0) {
        state->field44 = 0;
        state->endpoint_callback = 0;
        if (endpoint != 0) {
            if (reverse == 0) {
                first = fn_801F99C0(&resources[resource_index], 0);
                state->direction_a = 1;
                state->direction_b = 1;
                state->time = fn_801F9A38(&resources[resource_index], 0);
                state->key = fn_801F9AA8(&resources[resource_index], 0);
            } else {
                first = fn_801F99C0(&resources[resource_index], 1);
                state->direction_a = -1;
                state->direction_b = -1;
                state->time = fn_801F9A38(&resources[resource_index], 1);
                state->key = fn_801F9AA8(&resources[resource_index], 1);
            }
            state->resource_index = resource_index;
            state->resource = &resources[resource_index];
            if (first == 0) {
                fallback.x = resources[resource_index].base.x;
                fallback.y = resources[resource_index].base.y;
                fallback.z = resources[resource_index].base.z;
                first = (short*)&fallback;
            }
            state->position.x = first[0];
            state->position.y = first[1];
            state->position.z = first[2];
            state->resource = &resources[resource_index];
            state->key = 0;
            state->mode = 5;
            state->endpoint_callback = fn_801F8234;
        } else if (interpolation_mode == 0) {
            if (state->previous == 0) {
                state->interpolation_mode = 0;
                state->field28 = lbl_80651464;
                state->field2C = lbl_80651464;
            }
            fn_801F800C(snapshot, state);
            state->interpolation_mode = use_callback;
            if (state->interpolation_mode == 1) {
                state->interpolated_time =
                    fn_801F89B4(snapshot, &sample, &resources[resource_index]);
            } else if (state->interpolation_mode == 2) {
                state->interpolated_time =
                    fn_801F8FAC(&sample, &resources[resource_index],
                                state->previous->interpolated_time);
            } else {
                state->interpolated_time =
                    fn_801F92F8(snapshot, &sample, &resources[resource_index]);
            }
            state->resource = &resources[resource_index];
            state->key = 0;
            fn_801F8994(state, &sample, resources[resource_index].speed);
            state->callback = fn_801F8264;
        } else {
            state->callback_object = lbl_8064C4E4;
            state->callback = fn_801F7FBC;
        }
    } else if (interpolation_mode == 0) {
        terminal_sample.x = resources[resource_index].base.x;
        terminal_sample.y = resources[resource_index].base.y;
        terminal_sample.z = resources[resource_index].base.z;
        state->resource = &resources[resource_index];
        state->key = 0;
        state->callback = 0;
        fn_801F8994(state, &terminal_sample, resources[resource_index].speed);
        state->mode = 4;
    } else {
        if (interpolation_mode != 0) {
            state->callback_object = lbl_8064C4E4;
            state->callback = fn_801F7FBC;
        }
    }
}
