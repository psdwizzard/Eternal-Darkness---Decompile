extern int fn_80128EE4(void *);
extern void fn_80129190(void *, int);

#pragma opt_propagation off
int fn_800C3A74(void *object, void *alternate)
{
    void *saved_object;
    int state;
    void *saved_alternate;

    saved_object = object;
    state = 6;
    saved_alternate = alternate;

    if (fn_80128EE4(saved_object) & 0x20) {
        if (saved_alternate != 0) {
            state = 5;
        }
        fn_80129190(saved_object, state);
    }
    return 1;
}
#pragma opt_propagation reset
