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
    short base[3];
    unsigned char pad06[0x5A];
    unsigned short spline_count;
    unsigned short pad62;
    SplineKey* spline_keys;
    unsigned short linear_count;
    unsigned short pad6A;
    LinearKey* linear_keys;
} MotionResource;

extern Vec3 lbl_8063D4EC[2];
extern const float lbl_80651464;
extern void fn_8017974C(short*, short*, Vec3*, float);
extern void fn_80179814(short*, short*, short*, short*, Vec3*, float);

float fn_801F8FAC(Vec3* output, MotionResource* resource, float time)
{
    int whole = (int)time;
    float amount = time - whole;
    float result = time;
    int index;

    if (resource == 0) {
        output->x = lbl_80651464;
        output->y = lbl_80651464;
        output->z = lbl_80651464;
        return lbl_80651464;
    }

    if (resource->spline_count != 0) {
        SplineKey* keys = resource->spline_keys;
        SplineKey* key = keys;
        int last = resource->spline_count - 1;
        int current_offset;
        int neighbor_offset;

        index = 0;
        while (whole > key->time && index < last) {
            key++;
            index++;
        }

        current_offset = index * 0x18;
        neighbor_offset = (index + 1) * 0x18;
        fn_80179814((short*)((unsigned char*)keys + current_offset + 4),
                    (short*)((unsigned char*)keys + neighbor_offset + 4),
                    (short*)((unsigned char*)keys + current_offset + 0x10),
                    (short*)((unsigned char*)keys + current_offset + 0xA), output, amount);
        keys = resource->spline_keys;
        result = *(int*)((unsigned char*)keys + current_offset) + amount *
                 (*(int*)((unsigned char*)keys + neighbor_offset) -
                  *(int*)((unsigned char*)keys + current_offset));
    } else if (resource->linear_count != 0) {
        LinearKey* keys = resource->linear_keys;
        LinearKey* key = keys;
        int last = resource->linear_count - 1;
        int neighbor;
        int current_offset;
        int neighbor_offset;

        index = 0;
        while (whole > key->time && index < last) {
            key++;
            index++;
        }

        neighbor = index - 1;
        if (neighbor < 0) {
            neighbor = index + 1;
        }
        current_offset = index * 0xC;
        neighbor_offset = neighbor * 0xC;

        lbl_8063D4EC[0].x = *(short*)((unsigned char*)keys + current_offset + 4);
        lbl_8063D4EC[0].y = *(short*)((unsigned char*)keys + current_offset + 6);
        lbl_8063D4EC[0].z = *(short*)((unsigned char*)keys + current_offset + 8);
        amount = (amount - lbl_8063D4EC[0].x) /
                 (*(int*)((unsigned char*)keys + neighbor_offset) -
                  *(int*)((unsigned char*)keys + current_offset));
        lbl_8063D4EC[1].x = *(short*)((unsigned char*)keys + neighbor_offset + 4);
        lbl_8063D4EC[1].y = *(short*)((unsigned char*)keys + neighbor_offset + 6);
        lbl_8063D4EC[1].z = *(short*)((unsigned char*)keys + neighbor_offset + 8);
        fn_8017974C((short*)((unsigned char*)keys + current_offset + 4),
                    (short*)((unsigned char*)keys + neighbor_offset + 4),
                    output, amount);
        keys = resource->linear_keys;
        result = *(int*)((unsigned char*)keys + current_offset) + amount *
                 (*(int*)((unsigned char*)keys + neighbor_offset) -
                  *(int*)((unsigned char*)keys + current_offset));
    } else {
        output->x = resource->base[0];
        output->y = resource->base[1];
        output->z = resource->base[2];
    }
    return result;
}
