typedef unsigned char u8;
typedef signed short s16;

typedef struct State {
    u8 pad[0x38];
    void* resource;
    float ratio;
} State;

typedef struct Vector {
    float x;
    float y;
    float z;
} Vector;

extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern State* fn_8006D444(void*);
extern void *fn_80201814(void*);
extern int fn_80038308(void*, int, s16*);
extern int fn_80038464(void*, int, s16*);
extern int fn_800460EC(void);
extern int fn_8015E4E8(void);
extern void* fn_8007D944(void);
extern void* fn_8015C910(void);
extern int fn_800891FC(void);
extern void fn_801FA66C(int, int, float);
extern void fn_801FA748(int, Vector*);
extern unsigned int lbl_8064C920;
extern int lbl_8064D18C;
extern const float lbl_8064EB7C;
extern const Vector lbl_8023953C;

void fn_80088F4C(void)
{
    State* state;
    void* resource;
    void* object;
    int enabled;
    int valid;
    s16 maximum;
    s16 current;

    resource = fn_80204844(fn_80201B9C(), 0x20);
    if (resource == 0) {
        return;
    }
    state = fn_8006D444(resource);
    if (state == 0) {
        return;
    }
    object = fn_80201814(state->resource);
    if (object == 0) {
        return;
    }
    enabled = fn_80038308(object, 1, &maximum);
    valid = fn_80038464(object, 1, &current);
    if (current > 0 && valid != 0 && enabled != 0 &&
        fn_800460EC() == 0 && fn_8015E4E8() == 0 && fn_8007D944() == 0 &&
        fn_8015C910() == 0 && lbl_8064C920 == 0 && lbl_8064D18C != 5) {
        state->ratio = (float)maximum / (float)current;
        if (state->ratio <= lbl_8064EB7C) {
            int random = fn_800891FC();
            float factor = (float)random;
            fn_801FA66C(2, 1, factor * (lbl_8064EB7C - state->ratio));
        }
    } else {
        Vector value = lbl_8023953C;
        fn_801FA748(2, &value);
    }
}
