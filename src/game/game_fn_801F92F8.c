typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SplineKey {
    int time;
    short first[3];
    short second[3];
    short third[3];
    short pad;
} SplineKey;
typedef struct LinearKey { int time; short position[3]; short pad; } LinearKey;
typedef struct MotionResource {
    short base[3];
    unsigned char pad06[0x5A];
    unsigned short spline_count;
    unsigned short pad62;
    SplineKey* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    LinearKey* linear_keys;
} MotionResource;

extern float lbl_80651464;
extern float lbl_806514AC;
extern float lbl_806514B0;
extern float lbl_806514B8;
extern double lbl_80651470;
extern float fn_8017968C(Vec3*, Vec3*);
extern float fn_801796D4(float, float, float, float, float, float);
extern void fn_8017974C(short*, short*, Vec3*, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);

float fn_801F92F8(Vec3* point, Vec3* output, MotionResource* resource)
{
    float best = lbl_806514B0;
    float neighbor_distance = lbl_806514B0;
    int best_index = 0;
    int neighbor;
    int i;

    if (resource->spline_count != 0) {
        for (i = 0; i < resource->spline_count; i++) {
            SplineKey* key = &resource->spline_keys[i];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key->first[0], key->first[1], key->first[2]);
            if (distance < best) {
                best = distance;
                best_index = i;
            }
        }
        neighbor = best_index + 1;
        if (neighbor < resource->spline_count) {
            SplineKey* key = &resource->spline_keys[neighbor];
            neighbor_distance = fn_801796D4(point->x, point->y, point->z,
                                             key->first[0], key->first[1], key->first[2]);
        }
        if (best_index - 1 > 0) {
            SplineKey* key = &resource->spline_keys[best_index - 1];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key->first[0], key->first[1], key->first[2]);
            if (distance < neighbor_distance) neighbor = best_index - 1;
        }
        {
            float amount = lbl_806514AC;
            float step = lbl_806514B0;
            SplineKey* a = &resource->spline_keys[best_index];
            SplineKey* b = &resource->spline_keys[neighbor];
            fn_80179814(a->first, b->first, a->third, a->second, output, amount);
            while (step > lbl_806514B8) {
                float distance = fn_8017968C(point, output);
                if (distance < best) { best = distance; amount += step; }
                else amount -= step;
                step = (float)(step * lbl_80651470);
                fn_80179814(a->first, b->first, a->third, a->second, output, amount);
            }
            return a->time + amount * (b->time - a->time);
        }
    }
    if (resource->linear_count != 0) {
        for (i = 0; i < resource->linear_count; i++) {
            LinearKey* key = &resource->linear_keys[i];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key->position[0], key->position[1], key->position[2]);
            if (distance < best) { best = distance; best_index = i; }
        }
        neighbor = best_index + 1;
        if (neighbor >= resource->linear_count) neighbor = best_index - 1;
        fn_8017974C(resource->linear_keys[best_index].position,
                    resource->linear_keys[neighbor].position, output, lbl_806514AC);
        return resource->linear_keys[best_index].time;
    }
    output->x = resource->base[0];
    output->y = resource->base[1];
    output->z = resource->base[2];
    return lbl_80651464;
}
