typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 pad00[0x30];
    void* linked;
    u8 pad34[0xFBC];
    u8 flags;
} Object;

extern u32 lbl_8064D548;
extern u32 lbl_8064D54C;
extern u32 fn_80201B54(void*);
extern void fn_8020123C(int, u32, u32, int);
extern void fn_8011E174(int, int);
extern void fn_801D1318(int);
extern void fn_801D0E78(Object*);

void fn_801DC418(Object* object)
{
    u32 id;

    if (object->linked != 0) {
        id = fn_80201B54(object->linked);
        fn_8020123C(0x39, id, id, 0);
    }
    if (object->flags & 0x10) {
        fn_8011E174(0x800, 0);
        lbl_8064D54C = 0;
        lbl_8064D548 = 0;
        fn_801D1318(0);
    }
    fn_801D0E78(object);
}
