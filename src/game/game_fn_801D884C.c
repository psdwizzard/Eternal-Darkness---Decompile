typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern void* fn_80201B54(void*);
extern void fn_8020123C(u32, void*, void*, u32);
extern void fn_801D1318(u32);
extern void fn_80201814(u32);
extern void fn_80201BC8(void);
extern const float lbl_806510F8;
extern void fn_80121104(float);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);

void fn_801D884C(Object* object)
{
    void* value;

    if (*(void**)(object->bytes + 0x30) != 0) {
        value = fn_80201B54(*(void**)(object->bytes + 0x30));
        fn_8020123C(0x39, value, value, 0);
    }
    if (object->bytes[0xFF0] & 0x10) {
        fn_801D1318(0);
    }
    fn_80201814(*(u32*)(object->bytes + 0x0C));
    fn_80201BC8();
    fn_80121104(lbl_806510F8);
    fn_801A9E40(-1);
    fn_801D0E78(object);
}
