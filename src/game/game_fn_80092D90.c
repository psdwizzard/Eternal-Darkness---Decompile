typedef unsigned int u32;

typedef struct Vec3_80092D90 {
    float x, y, z;
} Vec3_80092D90;

typedef struct RuntimeInfo80092D90 {
    unsigned char pad00[0x68];
    void* value68;
} RuntimeInfo80092D90;

typedef struct State80092D90 {
    u32 flags;
    unsigned char pad04[0xC8];
    u32 entry_id;
} State80092D90;

typedef struct Entry80092D90 {
    u32 id;
    Vec3_80092D90 position;
} Entry80092D90;

typedef struct QueryResult80092D90 {
    void* object;
} QueryResult80092D90;

extern float lbl_8064EC78;
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void fn_80094DD0(void*, void*, void*);
extern void fn_800931D0(void*, void*, State80092D90*);
extern int fn_80092C30(void*, void*);
extern unsigned long long fn_8020123C();
extern int fn_80093148(void*, void*);
extern Entry80092D90* fn_800935CC(int, void*, u32, int);
extern QueryResult80092D90* fn_800BC100(int, Vec3_80092D90*, int*, int,
                                       int, int, int);
extern void fn_800BCCC4(void*, Vec3_80092D90*);
extern void fn_80201DD8(void*, int);
extern void fn_80201F44(void*, Vec3_80092D90*);
extern void fn_800BE010(void*, State80092D90*);
extern void fn_800BDEE4(void*, State80092D90*);
extern int fn_8009A2B8(void*, void*, void*, State80092D90*, void*, int, int,
                       int, float);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

int fn_80092D90(void* object, void* arg2,
                void* arg3, void* arg4,
                State80092D90* state)
{
    void* target;
    void* runtime;
    Entry80092D90* entry;
    int lookup;
    Vec3_80092D90 position;
    Vec3_80092D90 copied_position;
    int result = 0;

    target = ((RuntimeInfo80092D90*)fn_80201B8C(object))->value68;
    runtime = fn_80201B94(object);
    fn_80094DD0(object, arg2, arg4);
    fn_800931D0(object, arg3, state);

    if (fn_80092C30(object, target)) {
        fn_8020123C(0xA7, arg3, arg3, 0);
        fn_80094DD0(object, arg2, arg4);
    } else if ((state->flags & 0x800) && (state->flags & 0x80)) {
        fn_80093148(object, arg3);
    } else if (state->flags & 0x800) {
        fn_80093148(object, arg3);
    } else {
        QueryResult80092D90* found;
        lookup = -1;
        entry = fn_800935CC(0, 0, state->entry_id, 4);
        if (entry != 0)
            found = fn_800BC100(0, &entry->position, &lookup, 2, 0, 0, 0);
        else
            found = 0;

        if (entry != 0 && found != 0) {
            fn_800BCCC4(found->object, &position);
            fn_80201DD8(runtime, -1);
            copied_position = position;
            fn_80201F44(object, &copied_position);
            fn_800BE010(object, state);
            fn_800BDEE4(object, state);
            if (fn_8009A2B8(object, arg2, arg3, state, arg4, 2, 0x32, 1,
                            lbl_8064EC78)) {
                fn_80201D2C(object, 0x3F);
                fn_80201D14(object, 1);
                result = 1;
            }
        } else {
            state->entry_id = 0;
            fn_80201D2C(object, 0x3F);
            fn_80201D14(object, 1);
            result = 1;
        }
    }
    return result;
}
