extern void **fn_800C96C4(void);
extern void **fn_800C96CC(void);

void fn_80047D14(void **arg0, void **arg1)
{
    void **first = fn_800C96C4();
    void **second = fn_800C96CC();

    *arg0 = *first;
    *arg1 = *second;
}
