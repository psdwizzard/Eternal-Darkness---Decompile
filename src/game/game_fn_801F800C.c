typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef float Matrix34[3][4];

extern Vec3 lbl_8023B7FC;
extern Vec3 lbl_8023B808;
extern void* lbl_8064C4E4;

extern void fn_8011F114(Vec3*, void*);
extern void* fn_8011FE34(void*);
extern void fn_802114E0(Matrix34, void*);
extern void fn_80211710(Matrix34, Vec3*, Vec3*);

#pragma opt_lifetimes off
void fn_801F800C(Vec3* output, void* state)
{
    Vec3 offset = lbl_8023B7FC;
    Vec3 position;
    Matrix34 matrix;
    void* object = lbl_8064C4E4;
    void* parent;

    offset.y = *(float*)((unsigned char*)state + 0x28);
    offset.z = *(float*)((unsigned char*)state + 0x2C);
    if (*(void**)((unsigned char*)state + 0x68) != 0) {
        object = *(void**)((unsigned char*)state + 0x68);
    }

    *output = lbl_8023B808;
    if (object != 0) {
        parent = fn_8011FE34(object);
        fn_8011F114(&position, object);

        if (state != 0 && *(int*)((unsigned char*)state + 0x3C) != 0) {
            Vec3* source = *(Vec3**)((unsigned char*)state + 0x74);
            if (source != 0) {
                position = *source;
            }
            offset.x = *(float*)((unsigned char*)state + 0x54) *
                       *(float*)((unsigned char*)state + 0x28);
            offset.y = *(float*)((unsigned char*)state + 0x58) *
                       *(float*)((unsigned char*)state + 0x28);
            offset.z = *(float*)((unsigned char*)state + 0x5C) *
                       *(float*)((unsigned char*)state + 0x28);
            offset.z += *(float*)((unsigned char*)state + 0x2C);
        } else {
            fn_802114E0(matrix, parent);
            fn_80211710(matrix, &offset, &offset);
        }

        output->x = offset.x + position.x;
        output->y = offset.y + position.y;
        output->z = offset.z + position.z;
    }
}
#pragma opt_lifetimes reset
