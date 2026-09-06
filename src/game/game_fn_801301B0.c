typedef unsigned char u8;
typedef struct RuntimeState { u8 pad[0x54]; u8 flags; } RuntimeState;
typedef struct Object { u8 pad[0x290]; RuntimeState* runtime; } Object;
extern void fn_80125ECC(void *);
int fn_801301B0(Object* object, u8 clear, u8 set)
{
    RuntimeState* runtime;
    int value;

    fn_80125ECC(object);
    runtime = object->runtime;
    value = runtime->flags;
    runtime->flags = value & ~clear;
    runtime = object->runtime;
    runtime->flags = runtime->flags | set;
    return value;
}
