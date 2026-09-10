typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Object {
    Vec3 position;
    unsigned char pad0C[0x28];
    float value;
} Object;

void fn_801F8994(Object* object, const Vec3* position, float value)
{
    object->position.x = position->x;
    object->position.y = position->y;
    object->position.z = position->z;
    object->value = value;
}
