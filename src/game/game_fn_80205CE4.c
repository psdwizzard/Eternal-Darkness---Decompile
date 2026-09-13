typedef unsigned int u32;

extern void *fn_80156938(void);
extern void *fn_80201BC8(void *object);
extern void fn_8011F114(u32 *output, void *object);
extern void fn_80139F28(void *object, u32 *first, u32 *second, u32 *output,
                        int value);
extern void fn_8011F0E8(void *object, u32 *value);
extern void fn_8012D0D0(void *object);
extern int fn_8011FCB0(void *object);
extern void fn_8012A254(void *object);
extern void fn_80124DBC(void *object);
extern u32 fn_80178E94(u32 *first, u32 *second);
extern void *fn_80201B54(void *object);
extern void fn_8020123C(int type, void *first, void *second, int value);

int fn_80205CE4(void)
{
    u32 first[3];
    u32 second[3];
    void *owner = fn_80156938();
    void *object = fn_80201BC8(owner);

    if (object != 0) {
        fn_8011F114(first, object);
        fn_80139F28(object, first, first, second, 3);
        fn_8011F0E8(object, second);
        fn_8012D0D0(object);
        if (fn_8011FCB0(object) != 0) {
            fn_8012A254(object);
        } else {
            fn_80124DBC(object);
        }
    }

    if (fn_80178E94(first, second) == 0) {
        void *effect = fn_80201B54(owner);
        fn_8020123C(0x2F, effect, effect, 0);
    }
    return 0;
}
