typedef signed short s16;
typedef unsigned int u32;

typedef struct Object80201C8C Object80201C8C;

struct Object80201C8C {
    unsigned char padding[0x30];
    s16 value;
};

extern u32 fn_80201CCC(Object80201C8C *object);

s16 fn_80201C8C(Object80201C8C *object)
{
    if (fn_80201CCC(object) & 0x800) {
        return 150;
    }
    return object->value;
}
