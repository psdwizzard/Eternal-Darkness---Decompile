extern void *fn_80156938(void *);
extern int fn_80156FF4(void *);
extern int fn_801800F8(void *);
extern int fn_80180114(void *);
extern int fn_8018E934(void *);

int fn_801481BC(void *object, void *unused, int enabled)
{
    void *instance;
    int result = 0;

    if (enabled == 0)
        return 0;

    instance = fn_80156938(object);
    if (fn_801800F8(instance)) {
        if (fn_8018E934(instance))
            result |= 1;
        result |= 2;
    }
    if (fn_80180114(instance)) {
        fn_80156FF4(object);
        result |= 4;
    }
    return result;
}
