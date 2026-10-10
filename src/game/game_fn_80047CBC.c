extern void **fn_800C96C4(void);
extern void **fn_800C96CC(void);

void fn_80047CBC(void **arg0, void **arg1)
{
    void **a = fn_800C96C4();
    void **b = fn_800C96CC();
    *a = *arg0;
    *b = *arg1;
}
