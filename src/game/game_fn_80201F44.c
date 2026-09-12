typedef struct Vec3_80201F44 Vec3_80201F44;
typedef struct Inner80201F44 Inner80201F44;
typedef struct Object80201F44 Object80201F44;

struct Vec3_80201F44 {
    float x;
    float y;
    float z;
};

struct Inner80201F44 {
    unsigned char padding[0x14];
    int value;
    unsigned char padding2[0xC];
    Vec3_80201F44 position;
};

struct Object80201F44 {
    unsigned char padding[0x24];
    Inner80201F44* inner;
};

void fn_80201F44(Object80201F44* object, Vec3_80201F44* position)
{
    if (object != 0) {
        object->inner->position.x = position->x;
        object->inner->position.y = position->y;
        object->inner->position.z = position->z;
        object->inner->value = -1;
    }
}
