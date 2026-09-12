typedef unsigned int u32;

typedef struct Object80202160 Object80202160;

struct Object80202160 {
    unsigned char padding[0x1C];
    u32 flags;
};

u32 fn_80202160(Object80202160* object)
{
    return object->flags & 8;
}
