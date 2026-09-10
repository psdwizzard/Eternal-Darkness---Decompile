typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PackedObject {
    u16 flags;
    u8 first_index;
    u8 second_index;
    float x;
    float y;
    u32 value;
} PackedObject;

typedef struct Object {
    float x;
    float y;
    void* first;
    void* second;
    u32 value;
} Object;

extern void* memset(void*, int, unsigned int);
extern void* fn_801FBA94(int, int);

void fn_801FBB84(PackedObject* packed, Object* object)
{
    memset(object, 0, sizeof(Object));
    object->x = packed->x;
    object->y = packed->y;
    object->value = packed->value;

    if (packed->flags & 1) {
        object->first = fn_801FBA94(packed->first_index, 0);
    }
    if (packed->flags & 2) {
        object->second = fn_801FBA94(packed->second_index, 1);
    }
}
