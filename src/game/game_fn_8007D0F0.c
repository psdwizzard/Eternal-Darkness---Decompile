typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;

typedef struct Object {
    void *primary;
    unsigned char *secondary;
} Object;

typedef struct ResourceObject {
    unsigned char pad[580];
    int value;
} ResourceObject;

typedef struct CallbackOwner {
    void *object;
} CallbackOwner;

typedef struct CallbackObject {
    char pad[0x70];
    void *callback_data;
} CallbackObject;

extern void *fn_80201B3C(void);
extern void *fn_802053B0(void *, void *);
extern void *fn_80205288(void *);
extern void *fn_80201BC8(void *);
extern s32 fn_8011EB04(ResourceObject *);
extern void fn_80124664(void *, s32, s32, float);
extern void *fn_80201B8C(void *);
extern void *fn_80201C24(void *);
extern u16 fn_80157948(Object *);
extern u16 fn_80157994(Object *);
extern void fn_80157A28(Object *, u16);
extern s32 fn_80204EC8(void *, void *);
extern int fn_801E8328(u32, u32);
extern s32 fn_80201B44(void);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern u32 fn_80157C98(void *, u32, u32);
extern const float lbl_8064E9A4;

/* Linked-item transfer callback (registered by fn_8007CD5C). */
s32 fn_8007D0F0(void *unused, Object *linked)
{
    void *current;
    Object *state;
    ResourceObject *resource;
    CallbackOwner *owner;
    void *related;
    s32 space;
    u16 count;

    current = fn_80201B3C();
    related = fn_802053B0(current, linked);
    resource = fn_80201BC8(fn_80205288(current));
    if (fn_8011EB04(resource) == 0x70) {
        fn_80124664(resource, 0x1A, 8, lbl_8064E9A4);
    }
    owner = current != 0 ? fn_80201B8C(current) : 0;
    if (linked != 0 && related != 0) {
        state = fn_80201C24(related);
        space = fn_80157948(linked);
        space -= fn_80157994(linked);
        if (fn_80157994(state) <= space) {
            fn_80157A28(linked, fn_80157994(state) + fn_80157994(linked));
            fn_80204EC8(current, related);
            fn_801E8328(2, (u32)related);
        } else {
            count = fn_80157994(state);
            fn_80157A28(state, count - (fn_80157948(linked) - fn_80157994(linked)));
            fn_80157A28(linked, fn_80157948(linked));
        }
        if (owner != 0 && owner->object != 0) {
            fn_8020123C(0x10, fn_80201B44(),
                        (s32)((CallbackObject *)owner->object)->callback_data,
                        (s32)linked);
        }
        fn_80157C98(linked, 0x20, 0);
    }
    return 1;
}
