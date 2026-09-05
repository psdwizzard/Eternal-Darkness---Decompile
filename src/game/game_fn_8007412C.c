typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Node {
    u8 pad_00[0x48];
    void *value;
} Node;

typedef struct Owner {
    u8 pad_00[0x8C];
    Node *node;
} Owner;

extern void* fn_80201B94();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void *fn_80201C48(void *);
extern unsigned long long fn_8020123C();

void fn_8007412C(void *object, int mode)
{
    void *first;
    void *second;
    Node *node;
    void *value;
    u64 result;

    first = fn_80201B94(object);
    second = (void *)fn_80201B54(object);
    node = ((Owner *)fn_80201B8C(object))->node;
    if (mode != 0) {
        value = node->value;
    } else {
        value = fn_80201C48(first);
        node->value = value;
    }
    result = fn_8020123C(0x6B, second, value, mode);
    if ((u32)(result & 0xFFFFFFFF) == 0) {
        fn_8020123C(0x74, second, second, 0);
    }
}
