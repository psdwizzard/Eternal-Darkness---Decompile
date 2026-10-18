typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern u8 lbl_8063C068[];

extern void fn_801F02A0(Vec3*);
extern void fn_80179B08(void*, Vec3*);
extern int fn_8018F0A0(void);
extern void PSMTXMultVec(void*, Vec3*, Vec3*);

void fn_80188C1C(u8* entry, void* context,
                 void (*callback)(void*, float, float, float, float, float))
{
    Vec3 original;
    Vec3 transformed_original;
    Vec3 transformed_offset;
    Vec3 adjusted;
    Vec3 working;
    Vec3 default_vec;
    float radius;
    float left;
    float right;
    float lower;
    float upper;

    fn_801F02A0(&default_vec);
    working = default_vec;
    fn_80179B08(entry + 0xA, &original);
    adjusted = original;
    adjusted.x += working.x * (float)entry[0x21];
    adjusted.y += working.y * (float)entry[0x21];
    if (fn_8018F0A0()) {
        adjusted.z -= (double)entry[0x21] * 2.25;
    } else {
        adjusted.z += (double)entry[0x21] * 2.25;
    }
    PSMTXMultVec(lbl_8063C068, &original, &transformed_original);
    PSMTXMultVec(lbl_8063C068, &adjusted, &transformed_offset);
    radius = (float)entry[0x21];
    left = transformed_original.x - radius;
    right = transformed_original.x + radius;
    if (fn_8018F0A0()) {
        lower = transformed_offset.y + radius;
        upper = transformed_original.y + radius;
    } else {
        lower = transformed_offset.y - radius;
        upper = transformed_original.y - radius;
    }
    callback(context, left, lower, right, upper, transformed_original.z);
}
