typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0xBD];
} Object;

extern u32 lbl_8064D54C;
extern int fn_80201B54(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_8011E174(int, int);
extern int fn_80201AE4(void);
extern void fn_801D1318(int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);

void fn_801D8268(Object* object)
{
    void* value;
    void* result;

    value = *(void**)(object->bytes + 0x30);
    if (value != 0) {
        result = (void*)fn_80201B54(value);
        fn_8020123C(0x39, result, result, 0);
    }

    if ((object->bytes[0xBC] & 2) != 0) {
        fn_8011E174(0x800, 0);
        lbl_8064D54C = 0;
    } else if (*(int*)(object->bytes + 0xC) == fn_80201AE4()) {
        fn_801D1318(0);
        fn_8011E174(0x800, 0);
        lbl_8064D54C = 0;
    }

    fn_801A9E40(-1);
    fn_801D0E78(object);
}
