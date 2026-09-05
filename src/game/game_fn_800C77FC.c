extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

int fn_800C77FC(int unused, void *object)
{
    register unsigned long object_r = (unsigned long)object;

    fn_80201D2C((void *)object_r, 38);
    fn_80201D14((void *)object_r, 1);
    return 1;
}
