typedef signed char s8;
typedef unsigned char u8;

typedef struct Object800A1E94 {
    u8 pad000[0x29E];
    s8 value;
} Object800A1E94;

extern unsigned int rand(void);
#define rand() ((int)rand())

int fn_800A1E94(Object800A1E94* object)
{
    object->value = rand() % 3 + 3;
    return object->value;
}
