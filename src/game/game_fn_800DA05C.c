extern void *fn_800A1D28(void *);
extern int fn_800A30AC(void *);
extern void fn_801296F8(void *, int);
extern void fn_800A270C(void *, void *, int);

#pragma opt_propagation off
int fn_800DA05C(void *context, void *object)
{
    void *saved_context = context;
    void *saved_object = object;

    if (fn_800A30AC(fn_800A1D28(saved_object)) != 0) {
        fn_801296F8(saved_context, 0x10000);
        fn_800A270C(saved_object, saved_context, 1);
    }
    return 1;
}
#pragma opt_propagation reset
