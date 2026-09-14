typedef signed int s32;

#pragma use_lmw_stmw on

extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern void *fn_80201814();
extern s32 fn_8003BD48(void *, void *);

#pragma opt_propagation off
s32 fn_800607BC(void *owner, void *resource)
{
    register void *resolved;
    register void *first;
    register void *second;
    register s32 result;

    result = 0;
    resolved = resource;
    first = fn_801A7498(resolved);
    second = fn_801A7490(resolved);
    resolved = fn_80201814(first);

    fn_80201814(second);
    if (resolved != 0) {
        result = fn_8003BD48(owner, resource);
    }
    return result;
}
#pragma opt_propagation reset
