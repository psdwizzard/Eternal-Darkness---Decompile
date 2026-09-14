typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern s32 fn_80201B54(void *);
extern void *fn_8004918C(void);
extern void *fn_80201BC8(void *);
extern void *fn_80158598(s32, s32);
extern s32 fn_80157FE0(void *, s32, s32);
extern void *fn_80201814();
extern void *fn_80201C24(void);
extern s32 fn_80157948(void *);
extern u16 fn_80157994(void *);
extern u32 fn_802053B0(void *, void *);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);
extern void *fn_801294DC(void *, s32, s32, s32);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, s32);
extern s32 fn_80129334(void *, s32, s32 *, s32);
extern s32 fn_80129364(void *, s32, s32, s32 *, s32);
extern void fn_80157A28(void *, s32);
extern void fn_80157C98(void *, s32, s32);
extern s32 fn_800A1438(s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80204810(void);
extern void fn_800BF238(void);
extern void fn_800BFF14(void);
extern void fn_800BF4C8(void);
extern void fn_800BFF84(void);
extern void fn_8007D4D8(void);
extern void fn_8007D0F0(void);

/* Multi-callback creation path. */
s32 fn_8007CD5C(void *object)
{
    s32 object_id;
    void *created;
    void *current;
    void *resource;
    void *target;
    s32 shifted_id;
    s32 index;
    s32 result;
    s32 result2;

    object_id = fn_80201B54(object);
    current = fn_8004918C();
    result = -1;
    resource = fn_80201BC8(object);
    fn_80157FE0(fn_80158598(object_id, 0), 2, 0);
    fn_80201814();
    target = fn_80201C24();
    if ((u16)fn_80157994(target) == (u16)fn_80157948(target)) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    } else if (fn_802053B0(object, target) == 0) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    } else {
        created = fn_801294DC(resource, 0xA0, 0, 6);
        if (created != 0) {
            shifted_id = object_id << 8;
            fn_80128C28(created, fn_80204810, shifted_id | 6);
            fn_80128C44(created, fn_80204810, shifted_id | 7);
            if (fn_80129334(resource, 1, &result, -1) == -1) {
                fn_80157A28(target, fn_80157948(target));
                fn_80157C98(target, 0x20, 0);
            } else {
                index = fn_80129364(resource, 1, 0, &result2, -1);
                if (fn_800A1438(0) != 0) {
                    result2 = 0x35;
                    fn_801287C4(created, fn_800BF238, current, 0x34);
                    fn_801287C4(created, fn_800BFF14, current, result2 - 1);
                    fn_801287C4(created, fn_800BF4C8, current, result2 + 1);
                    fn_801287C4(created, fn_800BFF84, current, result2 + 1);
                    fn_801287C4(created, fn_8007D4D8, current, result2 + 2);
                } else {
                    fn_801287C4(created, fn_8007D0F0, target, result);
                }
                (void)index;
            }
            fn_80201D2C(object, 0x4D);
            fn_80201D14(object, 1);
        }
    }
    return 1;
}
