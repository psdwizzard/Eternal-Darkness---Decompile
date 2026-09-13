extern void *fn_80156938(void);
extern void *fn_80201BC8(void *object);
extern void fn_801EC9A8(void *object);
extern void fn_80120A30(void *object, int value, int time);

void fn_80205C98(void)
{
    void *object = fn_80201BC8(fn_80156938());

    fn_801EC9A8(object);
    if (object != 0) {
        fn_80120A30(object, 0, 30000);
    }
}
