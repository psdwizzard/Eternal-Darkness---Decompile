typedef struct MotionResource {
    unsigned char pad00[0x60];
    unsigned short spline_count;
    unsigned short pad62[3];
    unsigned short linear_count;
} MotionResource;

int fn_801F9AA8(MotionResource* resource, int last)
{
    if (resource->linear_count != 0) {
        return last != 0 ? resource->linear_count - 1 : 0;
    } else if (resource->spline_count != 0) {
        return last != 0 ? resource->spline_count - 1 : 0;
    }

    return 0;
}
