typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Runtime Runtime;

typedef struct Object {
    u8 pad0[0x3C];
    void* definition;
    u8* runtimes;
    u8 pad44[0x11C];
    u8* entries;
} Object;

extern void fn_80128C50(Runtime*);
extern void fn_8011EBB8(Object*);

void fn_80126680(Object* object)
{
    int offset;
    int i;

    offset = 0;
    for (i = 0; i < 8; i++) {
        fn_80128C50((Runtime*)(object->runtimes + offset));
        offset += 0x110;
    }

    i = 0;
    offset = 0;
    while (i < *(u16*)((u8*)object->definition + 8)) {
        *(u32*)(object->entries + offset + 0x48) = 0;
        offset += 0x4C;
        i++;
    }
    fn_8011EBB8(object);
}
