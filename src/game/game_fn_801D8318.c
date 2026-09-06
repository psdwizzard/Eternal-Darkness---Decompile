typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0xFF6];
} Object;

extern int lbl_8064D18C;
extern const float lbl_806510EC;
extern const float lbl_806510F0;
extern void* fn_80201814(void*);
extern int fn_801E855C(int, void*, int);
extern void* fn_80155DB4(void*);
extern int fn_80157034(void*);
extern int fn_80157050(void*);
extern int fn_80201AE4(void);
extern void fn_801D7C24(u32, u32, int, int, float);
extern void fn_801FE22C(void*);
extern void fn_801B05B0(int, int);
extern void fn_801D8268(Object*);
extern void fn_801D7F7C(Object*, float);
extern void fn_801FE934(void*, int);

void fn_801D8318(Object* object)
{
    void* target;

    if (*(int*)(object->bytes + 8) != lbl_8064D18C ||
        (object->bytes[0xFF0] & 1) != 0) {
        if ((object->bytes[0xBC] & 2) == 0 &&
            *(u16*)(object->bytes + 0xFF4) != 0 &&
            *(u16*)(object->bytes + 0xFF4) < 180) {
            target = fn_80201814(*(void**)(object->bytes + 0xC4));
            if (target != 0 && fn_801E855C(2, target, 0) == 0 &&
                fn_80157034(fn_80155DB4(target)) == 0 &&
                fn_80157050(target) == 0) {
                fn_801D7C24(*(u32*)(object->bytes + 4),
                            *(u32*)(object->bytes + 0xC8),
                            *(int*)(object->bytes + 0xC) != fn_80201AE4(), 0,
                            lbl_806510EC);
            }
        }
        fn_801FE22C(*(void**)(object->bytes + 0x44));
        if (*(int*)(object->bytes + 0x10) != -1)
            fn_801B05B0(*(int*)(object->bytes + 0x10), 10);
        fn_801D8268(object);
    } else {
        switch (*(u16*)(object->bytes + 0xFF4)) {
        case 0:
            fn_801D7F7C(object, lbl_806510F0);
            fn_801FE934(*(void**)(object->bytes + 0x44), 10);
            break;
        case 180:
            target = fn_80201814(*(void**)(object->bytes + 0xC4));
            if (target != 0 && fn_801E855C(2, target, 0) == 0 &&
                fn_80157034(fn_80155DB4(target)) == 0 &&
                fn_80157050(target) == 0) {
                fn_801D7C24(*(u32*)(object->bytes + 4),
                            *(u32*)(object->bytes + 0xC8),
                            *(int*)(object->bytes + 0xC) != fn_80201AE4(), 1,
                            lbl_806510EC);
            }
            if (*(void (**)(Object*, void*))(object->bytes + 0x28) != 0)
                (*(void (**)(Object*, void*))(object->bytes + 0x28))(
                    object, *(void**)(object->bytes + 0x2C));
            fn_801D8268(object);
            break;
        }
    }
}
