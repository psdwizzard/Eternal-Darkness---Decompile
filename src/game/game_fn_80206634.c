extern int lbl_8064D18C;

extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern int fn_8011FB4C(void *);
extern int fn_8013B8C0(void *, void *);
extern void *fn_80201B54(void *);
extern void *fn_80201BC0(void *);

void *fn_80206634(void *arg)
{
    void *entry = fn_80201B9C();
    void *object;
    void *result = 0;

    while (entry != 0) {
        object = fn_80201BC8(entry);

        if (object != 0 && fn_8011FB4C(object) == lbl_8064D18C &&
            fn_8013B8C0(object, arg) != 0) {
            result = fn_80201B54(entry);
            break;
        }
        entry = fn_80201BC0(entry);
    }

    return result;
}
