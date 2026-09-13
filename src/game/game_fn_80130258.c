typedef unsigned char u8;
typedef struct RuntimeState { u8 pad[0x4C]; unsigned int mask; } RuntimeState;
typedef struct Object { u8 pad[0x290]; RuntimeState* runtime; } Object;
extern void fn_80125ECC(void *);
unsigned int fn_80130258(Object* object, unsigned int clear, unsigned int set)
{
    RuntimeState* runtime;
    int value;

    fn_80125ECC(object);
    runtime = object->runtime;
    value = runtime->mask;
    runtime->mask = value & ~clear;
    runtime = object->runtime;
    runtime->mask = runtime->mask | set;
    return value;
}
