extern void* fn_80201B94();
extern void *fn_80201C48(void *);
extern int fn_80201B54();
extern void fn_80129FD0(void *, int, int);
extern unsigned long long fn_8020123C();

int fn_800D3598(void *state, void *object)
{
    /* NonMatching: 136 bytes at 93.088234% with canonical GC/1.3.
     * Retail assigns object/id to r31 and value to r30. Aggregate-local
     * variants remove required temporary moves without fixing allocation. */
    void *value = fn_80201C48(fn_80201B94(object));
    int id = fn_80201B54(object);

    fn_80129FD0(state, 0x2300000, 0);
    fn_8020123C(159, id, value, 1);
    return 1;
}
