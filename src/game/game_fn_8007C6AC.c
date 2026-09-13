typedef unsigned int u32;
typedef int s32;

extern int fn_80201B54();
extern void *fn_8004918C(void);
extern void *fn_801A7778(void *);
extern void *fn_80201BC8();
extern s32 fn_8011EB04(void *);
extern u32 fn_801578AC(void *);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, s32);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern s32 fn_80129334(void *, s32, s32 *, s32);
extern s32 fn_80157948(void *);
extern void fn_80157A28(void *, s32);
extern void fn_80157C98(void *, s32, s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80204810(void);
extern void fn_8007D0F0(void);

/* NonMatching: honest reconstruction of the object creation and callback path. */
s32 fn_8007C6AC(void *object)
{
    s32 object_id;
    void *resource;
    void *manager;
    void *current;
    u32 kind;
    void *created;
    s32 shifted_id;
    s32 result;

    object_id = fn_80201B54(object);
    manager = fn_8004918C();
    result = -1;
    current = fn_801A7778(manager);
    kind = 10;
    resource = fn_80201BC8(object);
    if (fn_8011EB04(resource) == 0x51 && current != 0 && fn_801578AC(current) == 0x10)
        kind = 0xA0;
    created = fn_801294DC(resource, kind, 0, 6);
    if (created != 0) {
        fn_8004918C();
        resource = fn_80201BC8(object);
        shifted_id = object_id << 8;
        fn_80128C28(created, fn_80204810, shifted_id | 6);
        fn_80201D2C(object, 0x4D);
        fn_80201D14(object, 1);
        if (fn_80129334(resource, 1, &result, -1) == -1) {
            fn_80157A28(current, fn_80157948(current));
            fn_80157C98(current, 0x20, 0);
        } else {
            fn_801287C4(created, fn_8007D0F0, current, result);
        }
        fn_80128C28(created, fn_80204810, shifted_id | 6);
        fn_80128C44(created, fn_80204810, shifted_id | 7);
    }
    return 1;
}
