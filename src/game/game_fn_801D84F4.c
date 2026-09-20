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

typedef struct State {
    void* first;
    void* second;
    u8 pad_08[0x20];
    int active;
    void* entries[7];
    float angle;
    void* resource;
    u8 pad_50[0x2E];
    u8 flags;
} State;

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
    Point3s points[8];
    u8 flags = *(volatile u8*)(object->bytes + 0x13A);
    register Point3s* line;
    s16 count;
    register Object* saved_object;
    register State* state;
    int i;

    saved_object = object;
    state = (State*)(saved_object->bytes + 0xBC);

    if ((flags & 5) == 0 &&
        fn_80201814(state->first) == 0) {
        void* value = state->second;
        fn_8020123C(0x39, value, value, 0);
    }

    if (state->active != 0)
        return;

    if (state->resource != 0)
        fn_80142FCC(state->resource);

    i = fn_801CEB2C(*(u32*)(saved_object->bytes + 4));
    line = points;
    count = (s16)i;
    for (i = 0; i < count; i++) {
        float angle = state->angle +
            lbl_806510E4 * (float)i / (float)count;
        points[i].x = (s16)(*(float*)(saved_object->bytes + 0x38) +
                            lbl_806510E8 * fn_80048C2C(angle));
        points[i].y = (s16)(*(float*)(saved_object->bytes + 0x3C) +
                            lbl_806510E8 * fn_80048C50(angle));
        points[i].z = (s16)*(float*)(saved_object->bytes + 0x40);

        if (state->entries[i] != 0) {
            if ((state->flags & 8) != 0)
                fn_8017FD6C(state->entries[i]);
            else
                fn_8019B134(state->entries[i], 0);
        }
    }

    if ((state->flags & 8) == 0) {
        for (i = 0; i < count - 1; i++) {
            fn_801D7998(line, line + 1, saved_object);
            line++;
        }
        fn_801D7998(&points[i], &points[0], saved_object);
    }
    fn_801D0E78(saved_object);
}
