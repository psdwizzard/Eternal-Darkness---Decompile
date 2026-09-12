typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Object80204180 {
    char pad[0x34];
    void *transform;
} Object80204180;

extern void fn_80201E78(Vec3 *position, void *object);
extern u32 fn_80178E94(Vec3 *first, Vec3 *second);

int fn_80204180(Object80204180 *first, Object80204180 *second)
{
    Vec3 first_position;
    Vec3 second_position;
    Vec3 first_temporary;
    Vec3 second_temporary;
    int distance = -1;

    if (first != 0 && second != 0 && first->transform != 0 &&
        second->transform != 0) {
        fn_80201E78(&first_temporary, first);
        first_position = first_temporary;
        fn_80201E78(&second_temporary, second);
        second_position = second_temporary;
        distance = fn_80178E94(&first_position, &second_position);
    }

    return distance;
}
