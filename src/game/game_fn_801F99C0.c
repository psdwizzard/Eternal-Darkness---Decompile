typedef struct SplineKey {
    int time;
    short position[10];
} SplineKey;

typedef struct LinearKey {
    int time;
    short position[4];
} LinearKey;

typedef struct MotionResource {
    unsigned char pad00[0x60];
    unsigned short spline_count;
    unsigned short pad62;
    SplineKey* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    LinearKey* linear_keys;
} MotionResource;

short* fn_801F99C0(MotionResource* resource, int last)
{
    if (resource->linear_count != 0) {
        if (last != 0) {
            return resource->linear_keys[resource->linear_count - 1].position;
        }
        return resource->linear_keys[0].position;
    }

    if (resource->spline_count != 0) {
        if (last != 0) {
            return resource->spline_keys[resource->spline_count - 1].position;
        }
        return resource->spline_keys[0].position;
    }

    return 0;
}
