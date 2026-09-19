typedef unsigned short u16;
typedef int s32;

extern int fn_80201B54();
extern void *fn_8004918C(void);
extern void *fn_80201BC8();
extern void *fn_801294DC(void *, int, int, int);
extern int fn_80201B44();
extern void *fn_80201814();
extern void *fn_801A7778(void *);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, s32);
extern u16 fn_80157994(void *);
extern s32 fn_80157948(void *);
extern unsigned int fn_802053B0(void *, void *);
extern void* fn_80201C24();
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern s32 fn_80129334(void *, s32, s32 *, s32);
extern void fn_80157A28(void *, s32);
extern void fn_80157C98(void *, s32, s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80204810(void);
extern void fn_8007CFB0(void);

/* NonMatching: honest reconstruction of the target-sensitive creation path. */
s32 fn_8007C90C(void *object)
{
    void *resource;
    register void *created;
    register void *target;
    register void *current;
    register s32 object_id;
    s32 count;
    s32 target_index;
    s32 result = -1;

    object_id = fn_80201B54(object);
    fn_8004918C();
    resource = fn_80201BC8(object);
    if ((created = fn_801294DC(resource, 10, 0, 6)) != 0) {
        current = fn_8004918C();
        fn_80201B44();
        fn_80201814();
        target = fn_801A7778(current);
        fn_80128C44(created, fn_80204810, (object_id << 8) | 7);
        target_index = (u16)fn_80157994(target) + 1;
        count = (u16)fn_80157948(target);
        if (count == target_index) {
            fn_80128C28(created, fn_80204810, (object_id << 8) | 6);
        } else if (fn_802053B0(object, target) != 0) {
            if ((u16)fn_80157994(fn_80201C24()) != 1)
                fn_80128C28(created, fn_80204810, (object_id << 8) | 0xB3);
            else
                fn_80128C28(created, fn_80204810, (object_id << 8) | 6);
        }
        resource = fn_80201BC8(object);
        fn_80201D2C(object, 0x48);
        fn_80201D14(object, 1);
        if (fn_80129334(resource, 1, &result, -1) == -1) {
            fn_80157A28(target, fn_80157948(target));
            fn_80157C98(target, 0x20, 0);
            fn_80128C28(created, fn_80204810, (object_id << 8) | 6);
        } else {
            fn_801287C4(created, fn_8007CFB0, current, result);
        }
    }
    return 1;
}
