typedef unsigned int u32;

typedef struct Object80201CCC Object80201CCC;

struct Object80201CCC {
    unsigned char padding[8];
    u32 value;
};

u32 fn_80201CCC(Object80201CCC *object)
{
    return object->value;
}
