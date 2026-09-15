typedef int s32;

extern int fn_80201B54();
extern void *fn_8004918C(void);
extern void *fn_80201BC8();
extern void *fn_801294DC(void *, int, int, int);
extern void *fn_80158598(s32, s32);
extern s32 fn_80157FE0(void *, s32, s32);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, s32);
extern s32 fn_80129364(void *, s32, s32, s32 *, s32);
extern void *fn_80201814();
extern void* fn_80201C24();
extern s32 fn_80157948(void *);
extern void fn_80157A28(void *, s32);
extern void fn_80157C98(void *, s32, s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80204810(void);
extern void fn_8007D0F0(void);

/* NonMatching: honest reconstruction of the paired target creation path. */
s32 fn_8007CB6C(void *object)
{
    void *resource;
    s32 object_id;
    void *created;
    s32 first;
    void *second;
    s32 lookup;
    s32 result;

    object_id = fn_80201B54(object);
    fn_8004918C();
    result = -1;
    resource = fn_80201BC8(object);
    created = fn_801294DC(resource, 10, 0, 6);
    if (created != 0) {
        fn_8004918C();
        first = fn_80157FE0(fn_80158598(object_id, 0), 1, 0);
        fn_80128C28(created, fn_80204810, (object_id << 8) | 6);
        fn_80128C44(created, fn_80204810, (object_id << 8) | 7);
        lookup = fn_80129364(resource, 1, 14, &result, -1);
        if (first == -1) {
            fn_80157FE0(fn_80158598(object_id, 0), 2, 0);
            fn_80201814();
            second = fn_80201C24();
            if (lookup == -1) {
                fn_80157A28(second, fn_80157948(second));
                fn_80157C98(second, 0x20, 0);
            } else {
                fn_801287C4(created, fn_8007D0F0, second, result);
            }
        } else {
            fn_80201814(first);
            second = fn_80201C24();
            if (lookup == -1) {
                fn_80157A28(second, fn_80157948(second));
                fn_80157C98(second, 0x20, 0);
                fn_80157FE0(fn_80158598(object_id, 0), 2, 0);
                fn_80201814();
                second = fn_80201C24();
                fn_80157A28(second, fn_80157948(second));
                fn_80157C98(second, 0x20, 0);
            } else {
                fn_801287C4(created, fn_8007D0F0, second, result);
            }
        }
        fn_80201D2C(object, 0x5A);
        fn_80201D14(object, 1);
    }
    return 1;
}
