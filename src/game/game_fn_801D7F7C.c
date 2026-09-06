typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object { u8 bytes[0xCC]; } Object;

extern const float lbl_806510EC;
extern void* fn_801D71A4(u32, void*, void*, u8, void**, void***, u32, float,
                         void**);
extern int fn_801D8710(u32);
extern float fn_801D86FC(u8);
extern void fn_800CD6C0(void*, u32, void*, u8, u32, int, void*, void*, float);
extern void* fn_80201B54(void);

void fn_801D7F7C(Object* object, float value)
{
    void* first;
    void** second;
    void* third;
    int result;
    void* handle = *(void**)(object->bytes + 0xC0);

    *(void**)(object->bytes + 0xC8) =
        fn_801D71A4(*(u32*)(object->bytes + 4), object->bytes + 0x38, handle,
                    *(u8*)(object->bytes + 0xBC), &first, &second,
                    *(u32*)(object->bytes + 8), lbl_806510EC, &third);
    result = fn_801D8710(*(u32*)(object->bytes + 4));
    fn_800CD6C0(handle, *(u32*)(object->bytes + 4), first,
                *(u8*)(object->bytes + 0xBC), *(u32*)(object->bytes + 8), result,
                object->bytes + 0x38, third,
                value + fn_801D86FC(*(u8*)(object->bytes + 0xBC)));
    *second = fn_80201B54();
    *(void**)(object->bytes + 0xC4) = *second;
}
