extern void *fn_801A7498(int value);
extern void *fn_80201814(void *object);
extern int fn_8011EB04(int object);
extern void fn_80149248(void *object, int value);

int fn_80203D30(int object, int value)
{
    void *resolved = fn_80201814(fn_801A7498(value));
    int type = fn_8011EB04(object);

    fn_80149248(resolved, (type == 0x5A) + 1);
    return 1;
}
