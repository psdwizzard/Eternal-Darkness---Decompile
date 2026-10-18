typedef signed char s8;
typedef unsigned char u8;

typedef struct Object800A1D4C {
    u8 pad000[0x29F];
    s8 value;
} Object800A1D4C;

extern unsigned int rand(void);
#define rand() ((int)rand())

int fn_800A1D4C(Object800A1D4C* object)
{
    object->value = rand() % 3;
    return object->value;
}
