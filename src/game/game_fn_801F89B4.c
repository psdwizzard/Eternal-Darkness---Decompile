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
    short base[3];
    unsigned char pad06[0x5A];
    unsigned short spline_count;
    unsigned short pad62;
    SplineKey* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    LinearKey* linear_keys;
} MotionResource;

extern float fn_8017968C(Vec3*, Vec3*);
extern float fn_801796D4(float, float, float, float, float, float);
extern void fn_8017974C(short*, short*, Vec3*, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);
extern const float lbl_80651464;
extern const double lbl_80651470;
extern const float lbl_806514A8;
extern const float lbl_806514AC;
extern const float lbl_806514B0;
extern const double lbl_806514B8;

float fn_801F89B4(Vec3* point, Vec3* output, MotionResource* resource)
{
    float best = lbl_806514A8;
    float other = best;
    float result = lbl_80651464;
    int best_index = 0;
    int neighbor;
    int i;

    if (resource->spline_count != 0) {
        for (i = 0; i < resource->spline_count; i++) {
            SplineKey* key = &resource->spline_keys[i];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key->first[0], key->first[1], key->first[2]);
            if (distance > best) {
                best = distance;
                best_index = i;
            }
        }

        neighbor = best_index + 1;
        if (neighbor < resource->spline_count) {
            SplineKey* key = &resource->spline_keys[neighbor];
            other = fn_801796D4(point->x, point->y, point->z,
                                key->first[0], key->first[1], key->first[2]);
        }
        if (best_index - 1 > 0) {
            SplineKey* key = &resource->spline_keys[best_index];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key[-1].first[0], key[-1].first[1], key[-1].first[2]);
            if (distance > other) {
                neighbor = best_index - 1;
            }
        }

        {
            int current_offset = best_index * 0x18;
            int neighbor_offset = neighbor * 0x18;
            short* current_third = (short*)((char*)resource->spline_keys + current_offset + 0x10);
            short* current_second = (short*)((char*)resource->spline_keys + current_offset + 0xA);
            float amount = lbl_806514B0;
            float step = lbl_806514AC;
            fn_80179814((short*)((char*)resource->spline_keys + current_offset + 4),
                        (short*)((char*)resource->spline_keys + neighbor_offset + 4),
                        current_third, current_second, output, amount);
            while (step > lbl_806514B8) {
                float distance = fn_8017968C(point, output);
                if (distance > best) {
                    best = distance;
                    amount += step;
                } else {
                    amount -= step;
                }
                step = (float)(step * lbl_80651470);
                fn_80179814((short*)((char*)resource->spline_keys + current_offset + 4),
                            (short*)((char*)resource->spline_keys + neighbor_offset + 4),
                            current_third, current_second, output, amount);
            }
            result = *(int*)((char*)resource->spline_keys + current_offset) + amount *
                (*(int*)((char*)resource->spline_keys + neighbor_offset) -
                 *(int*)((char*)resource->spline_keys + current_offset));
        }
    } else if (resource->linear_count != 0) {
        for (i = 0; i < resource->linear_count; i++) {
            LinearKey* key = &resource->linear_keys[i];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key->position[0], key->position[1], key->position[2]);
            if (distance > best) {
                best = distance;
                best_index = i;
            }
        }

        neighbor = best_index + 1;
        if (neighbor < resource->spline_count) {
            LinearKey* key = &resource->linear_keys[neighbor];
            other = fn_801796D4(point->x, point->y, point->z,
                                key->position[0], key->position[1], key->position[2]);
        }
        if (best_index - 1 > 0) {
            LinearKey* key = &resource->linear_keys[best_index];
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         key[-1].position[0], key[-1].position[1], key[-1].position[2]);
            if (distance < other) {
                neighbor = best_index - 1;
            }
        }

        {
            int current_offset = best_index * 0xC;
            int neighbor_offset = neighbor * 0xC;
            float amount = lbl_806514B0;
            float step = lbl_806514AC;
            fn_8017974C((short*)((char*)resource->linear_keys + current_offset + 4),
                        (short*)((char*)resource->linear_keys + neighbor_offset + 4),
                        output, amount);
            while (step > lbl_806514B8) {
                float distance = fn_8017968C(point, output);
                if (distance > best) {
                    best = distance;
                    amount += step;
                } else {
                    amount -= step;
                }
                step = (float)(step * lbl_80651470);
                fn_8017974C((short*)((char*)resource->linear_keys + current_offset + 4),
                            (short*)((char*)resource->linear_keys + neighbor_offset + 4),
                            output, amount);
            }
            result = *(int*)((char*)resource->linear_keys + current_offset) + amount *
                (*(int*)((char*)resource->linear_keys + neighbor_offset) -
                 *(int*)((char*)resource->linear_keys + current_offset));
        }
    } else {
        output->x = resource->base[0];
        output->y = resource->base[1];
        output->z = resource->base[2];
    }
    return result;
}
