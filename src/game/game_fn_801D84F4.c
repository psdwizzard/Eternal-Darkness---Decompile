typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef float f32;

typedef struct Point3s {
    s16 x;
    s16 y;
    s16 z;
} Point3s;

typedef struct Object {
    u8 bytes[0x13B];
} Object;

extern const float lbl_806510E4;
extern const double lbl_806510D8;
extern const float lbl_806510E8;
extern void* fn_80201814(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_80142FCC(void*);
extern int fn_801CEB2C(u32);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_8017FD6C(void*);
extern void fn_8019B134(void*, int);
extern void fn_801D7998(Point3s*, Point3s*, Object*);
extern void fn_801D0E78(Object*);

void fn_801D84F4(Object* object)
{
    Point3s points[16];
    u8* state = object->bytes + 0xBC;
    s16 count;
    int i;

    if ((object->bytes[0x13A] & 5) == 0 &&
        fn_80201814(*(void**)(state + 0)) == 0) {
        void* value = *(void**)(state + 4);
        fn_8020123C(0x39, value, value, 0);
    }

    if (*(int*)(state + 0x28) != 0)
        return;

    if (*(void**)(state + 0x4C) != 0)
        fn_80142FCC(*(void**)(state + 0x4C));

    count = (s16)fn_801CEB2C(*(u32*)(object->bytes + 4));
    for (i = 0; i < count; i++) {
        float angle = *(float*)(state + 0x48) +
            lbl_806510E4 * (float)i / (float)count;
        points[i].x = (s16)(*(float*)(object->bytes + 0x38) +
                            lbl_806510E8 * fn_80048C2C(angle));
        points[i].y = (s16)(*(float*)(object->bytes + 0x3C) +
                            lbl_806510E8 * fn_80048C50(angle));
        points[i].z = (s16)*(float*)(object->bytes + 0x40);

        if (*(void**)(state + 0x2C + i * 4) != 0) {
            if ((state[0x7E] & 8) != 0)
                fn_8017FD6C(*(void**)(state + 0x2C + i * 4));
            else
                fn_8019B134(*(void**)(state + 0x2C + i * 4), 0);
        }
    }

    if ((state[0x7E] & 8) == 0) {
        for (i = 0; i < count - 1; i++)
            fn_801D7998(&points[i], &points[i + 1], object);
        fn_801D7998(&points[i], &points[0], object);
    }
    fn_801D0E78(object);
}
