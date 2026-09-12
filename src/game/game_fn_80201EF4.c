typedef signed short s16;

typedef struct Object80201EF4 Object80201EF4;

struct Object80201EF4 {
    unsigned char padding[0x24];
    void* value;
};

extern int fn_80201C8C(void* value);

int fn_80201EF4(Object80201EF4* object, s16* output)
{
    int result = 0;

    if (object != 0 && object->value != 0) {
        *output = fn_80201C8C(object->value);
        result = 1;
    }
    return result;
}
