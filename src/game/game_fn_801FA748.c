typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectState {
    u8 pad00[0x48];
    Vec3 position;
    u8 pad54[0x34];
} ObjectState;

extern ObjectState lbl_8063CD18[];

void fn_801FA748(int index, Vec3* position)
{
    int offset = index * 0x88;
    ObjectState* objects = lbl_8063CD18;
    ObjectState* object = (ObjectState*)((u8*)objects + offset);

    object->position = *position;
}
