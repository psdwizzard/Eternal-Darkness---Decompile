extern int lbl_8064D18C;

extern int *fn_80200C38(void *object);
extern void fn_80200C20(void *object);
extern int fn_8011FB4C(void *object);
extern void fn_80201DE8(void *object, int value);
extern void fn_80201DF0(void *object, int value);
extern void *fn_801294DC(void *object, int type, int value, int flags);
extern int fn_8012A1FC(void *object, int type);
extern int fn_800459E0(void *object);
extern void fn_80129FD0(void *object, int value, int flags);
extern void fn_80128C28(void *object, void *callback, int type);
extern int fn_8012A1BC(void *object, int type);
extern void fn_801287C4(void *object, void *callback, int type, int value);
extern void fn_80201D2C(void *object, int value);
extern void fn_80201D14(void *object, int value);
extern void fn_80204810(void);

void *fn_80202440(void *object, int id, void *resource, void *target,
                  void *link, void *created)
{
    int *values;
    int first;
    int second;
    int group;
    int value;
    int type;
    void *result;

    values = fn_80200C38(link);
    first = values != 0 ? values[0] : 0;
    second = values != 0 ? values[1] : 0;
    group = fn_8011FB4C(resource);
    fn_80200C20(link);

    if (lbl_8064D18C == group || group == -1) {
        fn_80201DE8(target, second);
        fn_80201DF0(target, first);

        result = created != 0 ? created : fn_801294DC(resource, 0x19, 0x22, 8);
        created = result;

        if (result != 0) {
            fn_8012A1FC(resource, 0x19);
            if (fn_800459E0(object) == 0x28)
                fn_80129FD0(resource, 0x2C0000, 1);

            type = id << 8;
            fn_80128C28(result, fn_80204810, type | 0x15);

            if (second != 0) {
                value = first == -1 ? fn_8012A1FC(resource, 0x19) : first;
                fn_801287C4(result, fn_80204810, type | 6,
                            value == -2 ? fn_8012A1BC(resource, 0x19) : value);
            }

            fn_80201D2C(object, 0x10);
            fn_80201D14(object, 1);
        }
    }

    return created;
}
