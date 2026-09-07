typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0xFF1];
} Object;

extern u32 lbl_8064D548;
extern u32 lbl_8064D54C;

extern void* fn_80201B54(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_801D1318(int);
extern void fn_8011E174(int, int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);

void fn_801E237C(Object* object)
{
    void* value = *(void**)(object->bytes + 0x30);

    if (value != 0) {
        void* result = fn_80201B54(value);
        fn_8020123C(0x39, result, result, 0);
    }

    if ((object->bytes[0xFF0] & 0x10) != 0) {
        fn_801D1318(0);
        fn_8011E174(0x800, 0);
        lbl_8064D54C = 0;
        lbl_8064D548 = 0;
    }

    fn_801A9E40(-1);
    fn_801D0E78(object);
}
