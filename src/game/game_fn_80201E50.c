typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object80201E50 Object80201E50;

struct Object80201E50 {
    u8 padding[8];
    u32 value;
};

u32 fn_80201E50(Object80201E50* object, u32 value)
{
    u32 previous = object->value;
    object->value = value;
    return previous;
}
