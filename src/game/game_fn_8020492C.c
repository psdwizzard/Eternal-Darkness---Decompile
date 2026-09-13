extern void *fn_80201B9C(void);
extern void *fn_80201B54(void *object);
extern void *fn_80201BC0(void *object);
extern void *fn_80201C24(void *object);

void *fn_8020492C(void *value)
{
    void *object = fn_80201B9C();

    while (object != 0) {
        if (value == fn_80201C24(object)) {
            return fn_80201B54(object);
        }
        object = fn_80201BC0(object);
    }
    return 0;
}
