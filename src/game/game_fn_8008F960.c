typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SceneEntry {
    int mode;
    int value;
    short second;
    short third;
    short fourth;
    short fifth;
} SceneEntry;
typedef struct Wrapper { void* object; } Wrapper;
typedef struct Runtime { unsigned char pad[0x8C]; void* resource; } Runtime;

extern SceneEntry lbl_8031D3F8[][2][4];
extern int lbl_8064C560;
extern int lbl_8064C564;
extern int lbl_8064C578;
extern void* lbl_8064D18C;

extern int fn_80036D5C(void*);
extern int fn_80201EB8(void*);
extern void *fn_80201BC8();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void fn_80036DA4(void*, int);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern Wrapper* fn_800BC100(int, int, int*, int, int, int, int);
extern void fn_800BD194(void*, void*);
extern void fn_800BCCC4(void*, Vec3*);
extern void fn_80201DD8(void*, void*);
extern void fn_80201F44(void*, Vec3*);
extern void fn_800BDEE4(void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8008FB9C(void*, void*, void*, Vec3*, int*, void*, void*, Runtime*, void*);

void fn_8008F960(void* object, void* actor, int* link, void* state,
                 Runtime* runtime, void* extra)
{
    int flags = fn_80036D5C(object);
    int associated = fn_80201EB8(object);
    void* current = fn_80201BC8(object);
    Vec3 transform;

    fn_80201E78(&transform, object);
    fn_80036DA4(object, flags & ~0x100000);
    if (associated == (int)lbl_8064D18C) {
        int scene = lbl_8064C560;
        int id = lbl_8031D3F8[lbl_8064C578][scene][lbl_8064C564].fourth;
        lbl_8064C564 = 0;
        lbl_8064C560 = scene + 1;
        if (lbl_8064C560 >= 2 || lbl_8031D3F8[lbl_8064C578][lbl_8064C560][0].mode == 0) {
            link[5] = 0;
            fn_80201D34(object, 9);
            fn_80201D1C(object, 1);
        } else {
            Vec3 collision;
            Vec3 copied;
            Wrapper* wrapper = fn_800BC100(0, 0, &id, 16, 0, 0, 0);
            fn_800BD194(object, runtime->resource);
            fn_800BCCC4(wrapper->object, &collision);
            fn_80201DD8(state, (void*)-1);
            copied = collision;
            fn_80201F44(object, &copied);
            fn_800BDEE4(object, runtime->resource);
            fn_80201D2C(object, 3);
            fn_80201D14(object, 1);
        }
    } else {
        int next;
        lbl_8064C564 = 0;
        next = lbl_8064C560 + 1;
        lbl_8064C560 = next;
        if (next >= 2 || lbl_8031D3F8[lbl_8064C578][next][0].mode == 0) {
            link[5] = 0;
            fn_80201D34(object, 9);
            fn_80201D1C(object, 1);
        } else {
            Vec3 position = transform;
            fn_8008FB9C(object, current, actor, &position, link, state, extra,
                        runtime, runtime->resource);
        }
    }
}
