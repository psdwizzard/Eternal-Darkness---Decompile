typedef unsigned char u8;

typedef struct Vtable800A2B04 {
    u8 pad000[4];
    int (*select)(void*, int);
} Vtable800A2B04;

typedef struct State800A2B04 {
    Vtable800A2B04* vtable;
} State800A2B04;

typedef struct Context800A2B04 {
    u8 pad000[0x64];
    State800A2B04* state;
} Context800A2B04;

extern void *fn_80201B8C();
extern unsigned int rand(void);
#define rand() ((int)rand())

int fn_800A2B04(void* object, int value)
{
    Context800A2B04* context = ((Context800A2B04*)fn_80201B8C(object));
    int result = context->state->vtable->select(object, value);

    if (result == -1) {
        int random = (u8)rand();
        if (random <= 0x7F) {
            result = 4;
        } else {
            result = 5;
        }
    }
    return result;
}
