typedef struct Vec3 {
    float x, y, z;
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
    unsigned char pad00[0x24];
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
    unsigned char pad00[0xC];
    int time;
    unsigned char pad10[4];
    int key;
    unsigned char pad18[0x1C];
    float resource_speed;
    unsigned char pad38[0x44];
    MotionResource* resource;
} MotionState;

extern void fn_8017974C(short*, short*, Vec3*, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);

void fn_801F9AF8(MotionState* state, int requested_time, Vec3* output)
{
    Vec3 result;
    int done = 0;
    int index = 0;
    MotionResource* resource = state->resource;

    state->resource_speed = resource->speed;
    if (resource != 0) {
      while (!done) {
        if (resource->spline_count != 0) {
            SplineKey* current = &resource->spline_keys[index];
            SplineKey* next = &resource->spline_keys[index + 1];
            float amount = (float)(state->time - current->time) /
                           (float)(next->time - current->time);

            if (requested_time > next->time) {
                index++;
            } else if (requested_time < current->time) {
                index--;
            } else {
                fn_80179814(current->first, next->first, current->second,
                            next->third, &result, amount);
                done = 1;
            }

            if (state->key < 0 || state->key >= resource->spline_count) {
                return;
            }
        } else if (resource->linear_count != 0) {
            {
                LinearKey* current = &resource->linear_keys[index];
                LinearKey* next = &resource->linear_keys[index + 1];
                float amount = (float)(state->time - current->time) /
                               (float)(next->time - current->time);

                if (requested_time >= next->time) {
                    index++;
                } else if (requested_time < current->time) {
                    index--;
                } else {
                    fn_8017974C(current->position, next->position, &result,
                                amount);
                    done = 1;
                }
            }

            if (state->key < 0 || state->key >= resource->linear_count) {
                return;
            }
        } else {
            return;
        }
      }
        state->time = requested_time;
        state->key = index;
        *output = result;
    }
}
