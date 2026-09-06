typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Candidate80096710 {
    u8 pad00[0x14];
    int value;
} Candidate80096710;

typedef struct StateA80096710 {
    u8 pad00[0xCC];
    void* query;
} StateA80096710;

typedef struct StateB80096710 {
    u8 pad00[0x68];
    u8* record;
} StateB80096710;

extern void fn_80204810(void);
extern void *fn_80201BC8();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern Candidate80096710* fn_800935CC(int, void*, void*, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128C44(void*, void*, int);
extern void fn_80128C28();

int fn_80096710(void* arg_object, int arg_index,
                StateA80096710* arg_state_a,
                StateB80096710* arg_state_b)
{
    register void* object;
    register StateA80096710* state_a;
    register void* owner;
    register Candidate80096710* candidate;
    register StateB80096710* state_b;
    register int index;
    Vec3 position;

    object = arg_object;
    state_a = arg_state_a;
    state_b = arg_state_b;
    index = arg_index;
    owner = fn_80201BC8(object);
    fn_80201E78(&position, object);
    candidate = fn_800935CC(0, 0, state_a->query, 4);
    if (candidate == 0) {
        candidate = fn_800935CC(0, &position, 0, 1);
    }
    if (candidate == 0) {
        state_a->query = 0;
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
        return 1;
    }

    owner = fn_801294DC(owner, 0xA7, 0x30, 6);
    if (owner != 0) {
        fn_80128C44(owner, fn_80204810, (index << 8) | 7);
        fn_80128C28(owner, fn_80204810, (index << 8) | 0xDB);
        *(short*)(state_b->record + 0x30) = candidate->value;
        fn_80201D2C(object, 0x6D);
        fn_80201D14(object, 1);
        return 1;
    }
    return 0;
}
