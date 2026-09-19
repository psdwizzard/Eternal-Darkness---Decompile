typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec800A1278 {
    float x;
    float y;
    float z;
} Vec800A1278;

typedef struct Entry800A1278 {
    u8 field_00;
    u8 pad01[0x2B];
} Entry800A1278;

typedef struct Work800A1278 {
    u8 pad00[0x68];
    Vec800A1278 position;
} Work800A1278;

typedef struct State800A1278 {
    u8 pad00[0x38];
    u32 resource;
    u8 pad3C[0x2C];
    Entry800A1278 entries[1];
    u8 pad94[0x30];
    Work800A1278* work;
} State800A1278;

typedef struct Context800A1278 {
    u32 event;
    u8 pad04[4];
    short counter;
} Context800A1278;

typedef struct Inner800A1278 {
    u8 pad00[0x44];
    u32 resource;
} Inner800A1278;

typedef struct Info800A1278 {
    u8 pad00[0x8C];
    Inner800A1278* inner;
} Info800A1278;

extern void *fn_8006ED3C();
extern void *fn_80201814();
extern void *fn_80201BC8();
extern Vec800A1278* fn_8011F770(void*);
extern void fn_8011F114();
extern u8 fn_80128EE4(void*);
extern void fn_80211A48(const Vec800A1278*, const Vec800A1278*, Vec800A1278*);
extern Vec800A1278* fn_8011F130(void*);
extern void fn_8012AC74(void*, Vec800A1278*, int);
extern void *fn_80201B8C();
extern Inner800A1278* fn_80036D38(void*);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern void fn_8006DEF8(State800A1278*, u32, void*, void*, int);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((int)(a),(void*)(b),(void*)(c),(int)(d),(float)(e))
extern const Vec800A1278 lbl_802396E0;
extern float lbl_8064EE68;
extern float lbl_8064EDB8;

int fn_800A1278(State800A1278* state)
{
    int index;
    Context800A1278* context;
    Work800A1278* work;
    void* transform;
    Vec800A1278* position;
    Info800A1278* info;
    void* object;
    Vec800A1278 value;
    Vec800A1278 offset;
    int i;

    context = fn_8006ED3C(state, 0x23, &index);
    object = fn_80201814(state->resource);
    transform = fn_80201BC8(object);
    work = state->work;
    position = fn_8011F770(transform);
    fn_8011F114(&value, transform);
    fn_80128EE4(transform);

    if (context->counter == 0) {
        work->position = *position;
        context->counter++;
    }

    if (position->z < lbl_8064EE68) {
        offset = lbl_802396E0;
        fn_80211A48(position, &offset, position);
        fn_80211A48(fn_8011F130(transform), &offset, &offset);
        fn_8012AC74(transform, fn_8011F130(transform), 3);
    } else if (position->z >= lbl_8064EE68) {
        info = ((Info800A1278*)fn_80201B8C(object));
        fn_802020B4(fn_80201814(fn_80036D38(object)->resource), 0);
        fn_801A5C30(0);
        for (i = 0; i < 3; i++) {
            state->entries[index].field_00 = i;
            fn_8006DEF8(state, context->event, 0, 0, 0);
        }
        *position = work->position;
        fn_8012AC74(transform, &value, 3);
        fn_8020104C(0x51, 0, info->inner->resource, 0, lbl_8064EDB8);
    }
    return 0;
}
