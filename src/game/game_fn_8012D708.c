typedef signed short s16;

typedef struct ShortVec3 {
    s16 x;
    s16 y;
    s16 z;
} ShortVec3;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct TransformData {
    char pad[0x3C];
    ShortVec3 previous;
    ShortVec3 saved;
    ShortVec3 rotation;
    ShortVec3 current;
} TransformData;

extern void fn_8012BE18(const s16*, float*, int);
extern void fn_8012BDCC(const float*, s16*, int);

void fn_8012D708(TransformData* transform)
{
    ShortVec3 saved;
    Vec3 rotation;

    saved = transform->saved;
    transform->saved = transform->current;
    transform->previous = transform->saved;
    transform->current = saved;

    fn_8012BE18((s16*)&transform->rotation, (float*)&rotation, 8);
    rotation.x = -rotation.x;
    rotation.y = -rotation.y;
    rotation.z = -rotation.z;
    fn_8012BDCC((float*)&rotation, (s16*)&transform->rotation, 8);
}
