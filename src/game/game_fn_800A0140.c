typedef unsigned char u8;
typedef unsigned int u32;

typedef struct State800A0140 {
    u8 pad00[0x38];
    int resource;
    u8 pad3C[0x2C];
    u8 index;
} State800A0140;

typedef struct Context800A0140 {
    int mode;
    u8 pad04[4];
    short counter;
} Context800A0140;

typedef struct Object800A0140 {
    u8 pad00[0x44];
    int resource;
} Object800A0140;

typedef struct Info800A0140 {
    u8 pad00[0x8C];
    Object800A0140* owner;
} Info800A0140;

typedef struct Vec800A0140 {
    float x;
    float y;
    float z;
} Vec800A0140;

extern Context800A0140* fn_8006ED98(State800A0140*);
extern void fn_8006DEF8(State800A0140*, int, void*, void*, int);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern u32 fn_80128EE4(void);
extern void fn_800C1B50(int, int, int, float, float);
extern void fn_8011F114();
extern void fn_8012AC74(void*, Vec800A0140*, int);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((int)(a),(void*)(b),(void*)(c),(int)(d),(float)(e))
extern Object800A0140* fn_80036D38(void*);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern float lbl_8064C930;
extern float lbl_8064C934;
extern float lbl_8064EDB0;
extern float lbl_8064EDB8;
extern volatile float lbl_8064EE1C;
extern float lbl_8064EE20;
extern double lbl_8064EE28;
extern double lbl_8064EE30;

int fn_800A0140(void* argument)
{
    State800A0140* state;
    register void* transform;
    int i;
    Context800A0140* context;
    void* object;
    void* lateObject;
    void* finalObject;
    Vec800A0140 position;
    u32 input;
    int direction;
    Info800A0140* info;

    state = (State800A0140*)argument;
    context = fn_8006ED98(state);
    object = fn_80201814(state->resource);
    transform = fn_80201BC8(object);
    input = fn_80128EE4();
    if (lbl_8064C934 >= lbl_8064EE1C && lbl_8064C934 <= lbl_8064EE20 &&
        (input & 0xF) != 0) {
        direction = 2;
        if (lbl_8064C934 > lbl_8064EE28 && lbl_8064C934 < lbl_8064EE30) {
            direction = 1;
        }
        fn_800C1B50(state->resource, 15, direction,
                    lbl_8064C930 < lbl_8064EDB0 ? -lbl_8064C930 : lbl_8064C930,
                    lbl_8064C934);
        fn_8011F114(&position, transform);
        fn_8012AC74(transform, &position, 3);
        lbl_8064C934 += lbl_8064C930;
    } else if (lbl_8064C934 < lbl_8064EE1C || lbl_8064C934 > lbl_8064EE20) {
        context->counter++;
        if (context->counter >= 40) {
            for (i = 0; i < 3; i++) {
                state->index = i;
                fn_8006DEF8(state, context->mode, 0, 0, 0);
            }
            lateObject = fn_80201814(state->resource);
            info = ((Info800A0140*)fn_80201B8C());
            fn_8020104C(0x51, 0, info->owner->resource, 0, lbl_8064EDB8);
            finalObject = fn_80201814(fn_80036D38(lateObject)->resource);
            fn_800C1B50(state->resource, 15, 1, lbl_8064EDB8, lbl_8064EDB8);
            fn_8011F114(&position, transform);
            fn_8012AC74(transform, &position, 3);
            fn_802020B4(finalObject, 0);
            fn_801A5C30(0);
        }
    }
    return 1;
}
