extern void* lbl_8064C4E4;
extern int lbl_8064D6D8;

extern void* fn_80201B9C(void);
extern void* fn_80201BC8(void*);
extern void* fn_80201BC0(void*);
extern int fn_80201B4C(void*);
extern void* fn_80201EB8(void*);
extern int fn_8015E4E8(void);
extern void fn_801A5C30(int);
extern int fn_8015C628(void*);
extern void* fn_8011F950(void*);
extern void fn_801296F8(void*, int);
extern void fn_8011FB5C(void*, int);
extern void fn_801F60DC(void);
extern void fn_8018E8DC(int);

void fn_801F5240(int enabled)
{
    void* item;
    void* object;
    int mask = enabled ? 0 : 0x10000;

    item = fn_80201B9C();
    if (lbl_8064C4E4 != 0 && fn_8015E4E8() == 0) {
        fn_801A5C30(enabled ? 0 : 1);
    }
    while (item != 0) {
        object = fn_80201BC8(item);
        if (fn_80201B4C(item) != -1 && fn_8015C628(fn_80201EB8(item)) != 0 &&
            object != 0 && fn_8011F950(object) != 0) {
            fn_801296F8(object, mask);
            fn_8011FB5C(object, mask);
        }
        item = fn_80201BC0(item);
    }
    fn_801F60DC();
    fn_8018E8DC(mask);
    lbl_8064D6D8 = enabled != 0;
}
