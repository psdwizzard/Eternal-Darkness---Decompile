extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *object);
extern void *fn_80201C24(void *object);

void *fn_8020499C(void *value)
{
    void *object = fn_80201B9C();
    void *result = 0;

    while (object != 0) {
        if (value == fn_80201C24(object)) {
            result = object;
            break;
        }
        object = fn_80201BC0(object);
    }
    return result;
}
