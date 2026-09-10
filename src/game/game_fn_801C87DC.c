typedef unsigned int u32;
typedef struct FVec { float x, y, z; } FVec;

typedef struct Listener Listener;
typedef struct SoundPoint SoundPoint;

struct Listener {
    char pad00[0x10];
    u32 flags;
    float position[3];
    float velocity[3];
    float radius;
    float inner;
    float outer;
    float curve;
};

struct SoundPoint {
    SoundPoint* next;
    char pad04[8];
    u32 flags;
    float position[3];
    float scale;
    float velocity[3];
    float offset[3];
    char pad38[0x18];
    float matrix[12];
    float negative_limit;
    float positive_limit;
    float distance_scale;
    float gain;
};

extern SoundPoint* lbl_8064D4C0;
extern double __frsqrte(double);

extern void fn_801CA3D8(float*, float*, float*);
extern void fn_801CA484(float*);

static inline float magnitude(float value)
{
    static const double half = 0.5;
    static const double three_halves = 3.0;
    double estimate;
    volatile float result;

    if (value > 0.0f) {
        estimate = __frsqrte(value);
        estimate = half * estimate *
                   (three_halves - estimate * estimate * value);
        estimate = half * estimate *
                   (three_halves - estimate * estimate * value);
        estimate = half * estimate *
                   (three_halves - estimate * estimate * value);
        result = value * estimate;
        return result;
    }
    return value;
}

void fn_801C87DC(Listener* listener, float* gain, float* distance_mix,
                 float* direction_x, float* direction_y, float* vertical_mix)
{
    SoundPoint* point;
    float delta[3];
    float vel[3];
    float direction[3];
    float velocity_distance;
    float distance;
    float projected_distance;
    float prediction_scale;
    float ratio;
    FVec pan;
    u32 count;

    prediction_scale = 1.0f / 60.0f;
    *gain = 0.0f;
    *distance_mix = 1.0f;
    pan.x = pan.y = pan.z = 0.0f;
    count = 0;
    point = lbl_8064D4C0;

    while (point != 0) {
        delta[0] = listener->position[0] -
                   (point->position[0] + point->offset[0] * point->scale);
        delta[1] = listener->position[1] -
                   (point->position[1] + point->offset[1] * point->scale);
        delta[2] = listener->position[2] -
                   (point->position[2] + point->offset[2] * point->scale);
        distance = magnitude(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);

        if (listener->radius >= distance) {
            ratio = distance / listener->radius;

            if (listener->curve >= 0.0f) {
                *gain += point->gain *
                         (listener->outer +
                          (listener->inner - listener->outer) *
                              (1.0f -
                               ((1.0f - listener->curve) * ratio +
                                listener->curve * ratio * ratio)));
            } else {
                *gain += point->gain *
                         (listener->outer +
                          (listener->inner - listener->outer) *
                              (1.0f -
                               ((listener->curve + 1.0f) * ratio -
                                listener->curve *
                                    (1.0f - (1.0f - ratio) * (1.0f - ratio)))));
            }

            if (!(listener->flags & 0x00080000)) {
                if ((listener->flags & 0x00000008) || (point->flags & 1)) {
                    vel[0] = point->velocity[0] - listener->velocity[0];
                    vel[1] = point->velocity[1] - listener->velocity[1];
                    vel[2] = point->velocity[2] - listener->velocity[2];
                    velocity_distance = magnitude(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]);

                    if (velocity_distance > 0.0f) {
                        delta[0] = listener->position[0] + listener->velocity[0] * prediction_scale -
                                   (point->position[0] + point->velocity[0] * prediction_scale);
                        delta[1] = listener->position[1] + listener->velocity[1] * prediction_scale -
                                   (point->position[1] + point->velocity[1] * prediction_scale);
                        delta[2] = listener->position[2] + listener->velocity[2] * prediction_scale -
                                   (point->position[2] + point->velocity[2] * prediction_scale);
                        projected_distance = magnitude(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);

                        if (projected_distance < distance) {
                            *distance_mix = point->distance_scale /
                                            (point->distance_scale - velocity_distance);
                        } else {
                            *distance_mix = point->distance_scale /
                                            (point->distance_scale + velocity_distance);
                        }
                    }
                }

                if (distance != 0.0f) {
                    fn_801CA3D8(point->matrix, listener->position, direction);
                    if (direction[2] <= 0.0f) {
                        pan.z += -point->negative_limit < direction[2] ? -direction[2] / point->negative_limit : 1.0f;
                    } else {
                        pan.z += point->positive_limit > direction[2] ? -direction[2] / point->positive_limit : -1.0f;
                    }
                    if (0.0f != direction[0] ||
                        0.0f != direction[1] ||
                        0.0f != direction[2]) {
                        fn_801CA484(direction);
                    }
                    pan.x += direction[0];
                    pan.y -= direction[1];
                }
            }
        }
        point = point->next;
        count++;
    }

    if (count != 0) {
        *direction_x = pan.x / count;
        *direction_y = pan.y / count;
        *vertical_mix = pan.z / count;
    }
}
