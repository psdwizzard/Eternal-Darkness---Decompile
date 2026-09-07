typedef unsigned char u8;

typedef float Matrix[3][4];

extern void fn_80127DF8(void* object, int index, Matrix output);
extern void fn_80211484(Matrix output, float x, float y, float z);
extern void fn_802114B8(Matrix output, float x, float y, float z);
extern void fn_802114E0(Matrix output, void* angles);
extern void fn_80210FDC(Matrix left, Matrix right, Matrix output);

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

void fn_8011F41C(void* object, int index, int use_linked_index, Matrix output,
                 int apply_object_transform, int apply_record_rotation)
{
    u8* bytes = object;
    u8* owner = *(u8**)(bytes + 0x3C);
    u8* records = *(u8**)(owner + 0x24);
    u8* record = records + index * 0x50;
    Matrix record_transform;
    Matrix translation;
    Matrix rotation;
    Matrix linked_translation;
    int resolved = index;

    if (object == *(void**)(bytes + 0x174) && use_linked_index) {
        resolved = (*(u8**)(record + 0x3C) - records) / 0x50;
    }
    fn_80127DF8(object, resolved, output);

    if (object == *(void**)(bytes + 0x174) && use_linked_index) {
        Vec3* positions = *(Vec3**)(bytes + 0x154);
        fn_80211484(linked_translation, positions[index].x, positions[index].y,
                    positions[index].z);
        fn_80210FDC(output, linked_translation, output);
    }

    fn_802114B8(record_transform, *(float*)(record + 0), *(float*)(record + 4),
                *(float*)(record + 8));
    if (apply_record_rotation) {
        fn_80210FDC(record_transform, (float (*)[4])(record + 0x0C), record_transform);
    }
    fn_80210FDC(output, record_transform, output);

    if (apply_object_transform) {
        fn_80211484(translation, *(float*)(bytes + 0), *(float*)(bytes + 4),
                    *(float*)(bytes + 8));
        fn_802114E0(rotation, bytes + 0x2C);
        fn_80210FDC(translation, rotation, translation);
        fn_80210FDC(translation, output, output);
    }
}
