typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern void* fn_80201B54(void*);
extern void fn_8020123C(u32, void*, void*, u32);
extern void fn_801D1318(u32);
extern void fn_801D0E78(Object*);

void fn_801D31E0(Object* object)
{
    void* handle = *(void**)&object->bytes[0x30];

    if (handle != 0) {
        void* value = fn_80201B54(handle);
        fn_8020123C(0x39, value, value, 0);
    }
    if (object->bytes[0xFF0] & 0x10) {
        fn_801D1318(0);
    }
    fn_801D0E78(object);
}
