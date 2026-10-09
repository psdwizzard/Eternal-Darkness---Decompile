typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SplineKey { int time; short first[3]; short second[3]; short third[3]; short pad; } SplineKey;
typedef struct LinearKey { int time; short position[3]; short pad; } LinearKey;
typedef struct MotionResource {
    short base[3]; unsigned char pad06[0x5A]; unsigned short spline_count;
    unsigned short pad62; SplineKey* spline_keys; unsigned short linear_count;
    unsigned short pad6A; LinearKey* linear_keys;
} MotionResource;

extern float lbl_80651464;
extern float fn_8017968C(Vec3*, Vec3*);
extern float fn_801796D4(float, float, float, float, float, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);
extern void fn_8013C264(const Vec3*, const Vec3*, Vec3*, const Vec3*, Vec3*);
extern float fn_80211B44(const Vec3*, const Vec3*);

float fn_801F92F8(Vec3* point, Vec3* output, MotionResource* resource)
{
    float best = 3.4028235e38f;
    float neighbor_distance = 3.4028235e38f;
    float result = lbl_80651464;
    Vec3 first, second, direction, closest, query;
    int best_index = 0;
    int neighbor, i;

    if (resource->spline_count != 0) {
        for (i = 0; i < resource->spline_count; i++) {
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         resource->spline_keys[i].first[0],
                                         resource->spline_keys[i].first[1],
                                         resource->spline_keys[i].first[2]);
            if (distance < best) { best = distance; best_index = i; }
        }
        neighbor = best_index + 1;
        if (neighbor < resource->spline_count) {
            neighbor_distance = fn_801796D4(point->x, point->y, point->z,
                                            resource->spline_keys[neighbor].first[0],
                                            resource->spline_keys[neighbor].first[1],
                                            resource->spline_keys[neighbor].first[2]);
        }
        if (best_index - 1 > 0) {
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         resource->spline_keys[best_index - 1].first[0],
                                         resource->spline_keys[best_index - 1].first[1],
                                         resource->spline_keys[best_index - 1].first[2]);
            if (distance < neighbor_distance) neighbor = best_index - 1;
        }
        {
            short* third = resource->spline_keys[best_index].third;
            short* second_ctl = resource->spline_keys[best_index].second;
            float step = 0.25f;
            float amount = 0.5f;
            fn_80179814(resource->spline_keys[best_index].first, resource->spline_keys[neighbor].first,
                        third, second_ctl, output, amount);
            while (step > 0.0001) {
                float distance = fn_8017968C(point, output);
                if (distance < best) { best = distance; amount += step; }
                else amount -= step;
                step *= 0.5;
                fn_80179814(resource->spline_keys[best_index].first, resource->spline_keys[neighbor].first,
                            third, second_ctl, output, amount);
            }
            result = resource->spline_keys[best_index].time +
                     amount * (resource->spline_keys[neighbor].time - resource->spline_keys[best_index].time);
        }
    } else if (resource->linear_count != 0) {
        for (i = 0; i < resource->linear_count; i++) {
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         resource->linear_keys[i].position[0],
                                         resource->linear_keys[i].position[1],
                                         resource->linear_keys[i].position[2]);
            if (distance < best) { best = distance; best_index = i; }
        }
        neighbor = best_index + 1;
        if (neighbor < resource->linear_count) {
            neighbor_distance = fn_801796D4(point->x, point->y, point->z,
                                            resource->linear_keys[neighbor].position[0],
                                            resource->linear_keys[neighbor].position[1],
                                            resource->linear_keys[neighbor].position[2]);
        }
        if (best_index - 1 > 0) {
            float distance = fn_801796D4(point->x, point->y, point->z,
                                         resource->linear_keys[best_index - 1].position[0],
                                         resource->linear_keys[best_index - 1].position[1],
                                         resource->linear_keys[best_index - 1].position[2]);
            if (distance < neighbor_distance) neighbor = best_index - 1;
        }
        {
            float first_dot, interval, projection, amount;
            int start;
            first.x = resource->linear_keys[best_index].position[0];
            first.y = resource->linear_keys[best_index].position[1];
            first.z = resource->linear_keys[best_index].position[2];
            second.x = resource->linear_keys[neighbor].position[0];
            second.y = resource->linear_keys[neighbor].position[1];
            second.z = resource->linear_keys[neighbor].position[2];
            query.x = point->x; query.y = point->y; query.z = point->z;
            fn_8013C264(&first, &second, &direction, &query, &closest);
            output->x = closest.x; output->y = closest.y; output->z = closest.z;
            first_dot = fn_80211B44(&first, &direction);
            interval = fn_80211B44(&second, &direction) - first_dot;
            projection = fn_80211B44(&closest, &direction) - fn_80211B44(&first, &direction);
            amount = 0.0f;
            start = resource->linear_keys[best_index].time;
            if (interval != 0.0f)
                amount = projection / interval;
            result = start + amount * (resource->linear_keys[neighbor].time - start);
        }
    } else {
        output->x = resource->base[0]; output->y = resource->base[1]; output->z = resource->base[2];
    }
    return result;
}
