extern void* fn_80201B94();
extern int fn_80201C48(int);
extern int fn_80201B54();
extern void fn_80129FD0(void *, int, int);
extern unsigned long long fn_8020123C();

int fn_800D3598(void *state, void *object)
{
    /* NonMatching: behavior- and size-exact honest C at 93.088234%. Retail
     * keeps object/id in r31 and value in r30; GC/1.3 assigns them oppositely
     * and schedules the r30 save before the object move. */
    int value = fn_80201C48((int)fn_80201B94(object));
    int id = fn_80201B54(object);

    fn_80129FD0(state, 0x2300000, 0);
    fn_8020123C(159, id, value, 1);
    return 1;
}
