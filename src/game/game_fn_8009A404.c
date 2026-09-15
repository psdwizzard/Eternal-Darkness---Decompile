typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ActorData8009A404 {
    u8 pad00[0x8C];
    void* actor;
    u8 pad90[0xA];
    s16 kind;
} ActorData8009A404;

extern int fn_80200C10(void*);
extern void* fn_80201BC8(void*);
extern void* fn_80201B54(void*);
extern ActorData8009A404* fn_80201B8C(void*);
extern void* fn_80201B94(void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_80201EB8(void*);
extern void fn_800BD2DC(void*, void*);
extern void fn_800BD194(void*, void*);
extern void fn_800C9E50(void*);
extern void fn_8012B324(void*);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern void fn_801E8328(int, void*);
extern int fn_80200C38(void*);
extern void fn_801261F4(void*);
extern void fn_8012B388(void*);
extern void** fn_800BC100(int, int, int*, int, int, int, int);
extern void fn_800BCCC4(void*, Vec3*);
extern void fn_80201DD8(void*, int);
extern void fn_80201F44(void*, Vec3*);
extern void fn_800BDEE4(void*, void*);
extern void fn_8012C62C(void*, int, u32*, u32*, u32*, int);
extern void fn_800BE010(void*, void*);
extern int fn_80201C48(void*);
extern int fn_8009A2B8(void*, void*, void*, u8*, void*, void*, u32, int, float);
extern void fn_8020123C(int, int, void*, int);
extern int lbl_8064D18C;
extern u32 lbl_806519E4, lbl_8064ED18, lbl_8064ED14;
extern u32 lbl_8064ED20, lbl_8064ED1C, lbl_806519E8;
extern const float lbl_8064ED24;

int fn_8009A404(register void* object, register int phase, register void* event)
{
    register int kind;
    register void* actor;
    register void* context;
    register ActorData8009A404* data;
    register void* room;
    register void* actor_id;
    void** created;
    int value;
    Vec3 source;
    Vec3 position;
    u32 c, b, a;
    u32 f, e, d;

    kind = fn_80200C10(event);
    room = fn_80201BC8(object);
    actor_id = fn_80201B54(object);
    data = fn_80201B8C(object);
    actor = data->actor;
    context = fn_80201B94(object);
    if (phase == 0) {
        if (kind == 1) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x3D) {
            fn_800BD2DC(object, actor);
            return 1;
        } else if (kind == 0x3E) {
            fn_800BD194(object, actor);
            fn_800C9E50(object);
            return 1;
        } else if (kind == 0x39) {
            if (fn_80201EB8(object) == lbl_8064D18C) fn_8012B324(room);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        } else if (kind == 0x9D) {
            if (fn_80201EB8(object) == lbl_8064D18C) {
                value = fn_80200C38(event);
                fn_801261F4(room);
                fn_8012B388(room);
                created = fn_800BC100(0, 0, &value, 0x10, 0, 0, 0);
                if (created != 0) {
                    fn_800BD194(object, actor);
                    fn_800BCCC4(*created, &source);
                    fn_80201DD8(context, -1);
                    position = source;
                    fn_80201F44(object, &position);
                    fn_800BDEE4(object, data->actor);
                    fn_80201D2C(object, 3);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        } else if (kind == 0x11) {
            if (fn_80201EB8(object) == lbl_8064D18C) {
                fn_801261F4(room);
                a = lbl_806519E4; b = lbl_8064ED18; c = lbl_8064ED14;
                fn_8012C62C(room, 0xF, &c, &b, &a, 4);
            }
            return 1;
        } else if (kind == 0x10) {
            if (fn_80201EB8(object) == lbl_8064D18C) {
                fn_801261F4(room);
                d = lbl_8064ED20; e = lbl_8064ED1C; f = lbl_806519E8;
                fn_8012C62C(room, 0xF, &f, &e, &d, 4);
            }
            return 1;
        }
        goto zero;
    }
    if (phase == 1) goto zero;
    if (phase != 3) goto other_zero;
    if (kind != 3) goto zero;
    fn_800BE010(object, actor);
    if (fn_80201C48(context) != 0) fn_800BDEE4(object, actor);
    if (fn_8009A2B8(object, room, actor_id, (u8*)actor, event, (void*)2,
                    0x50, 0, lbl_8064ED24) != 0) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
        if (data->kind == 0x97) fn_8020123C(0x11, 0, actor_id, 0);
    }
    return 1;

other_zero:
    return 0;
zero:
    return 0;
}
