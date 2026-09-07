typedef unsigned char u8;

typedef struct Object {
    u8 pad0[0x30];
    void* field30;
    u8 pad34[0xFBC];
    u8 flagsFF0;
} Object;

extern void* fn_80201B54(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_801D1318(int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);

void fn_801E3314(Object* object)
{
    if (object->field30 != 0) {
        void* value = fn_80201B54(object->field30);
        fn_8020123C(57, value, value, 0);
    }
    if (object->flagsFF0 & 0x10) {
        fn_801D1318(0);
    }
    fn_801A9E40(-1);
    fn_801D0E78(object);
}
