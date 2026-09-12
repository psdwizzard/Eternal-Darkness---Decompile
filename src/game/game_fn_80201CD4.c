typedef unsigned int u32;

typedef struct Object80201CD4 Object80201CD4;

struct Object80201CD4 {
    unsigned char padding[0xC];
    u32 value;
};

u32 fn_80201CD4(Object80201CD4 *object)
{
    return object->value;
}
