typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    u32 x, y, z;
} Vec3;

typedef struct RuntimeState {
    Vec3 position;
    u8 pad0C[0x34];
    float scale;
    int state;
    u8 pad48[0xC];
    u8 flags;
    u8 index;
} RuntimeState;

typedef struct Object {
    u8 pad[0x290];
    RuntimeState* runtime;
} Object;

extern float lbl_806501DC;
extern void fn_80125ECC(void *);
extern int fn_8012FFE0(void*, int, int);

int fn_8012FF34(Object* object, Vec3* position, int flags, int index)
{
    register u32 x;
    register u32 y;
    register Vec3* destination;
    float one;
    int result;

    fn_80125ECC(object);
    result = fn_8012FFE0(object, flags, index);
    if (result) {
        destination = &object->runtime->position;
        x = position->x;
        y = position->y;
        one = lbl_806501DC;
        destination->x = x;
        destination->y = y;
        destination->z = position->z;
        object->runtime->flags = flags;
        object->runtime->state = 2;
        object->runtime->index = index;
        object->runtime->scale = one;
    }

    return result;
}
