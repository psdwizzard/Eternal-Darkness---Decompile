typedef unsigned int u32;

#pragma use_lmw_stmw on

extern u32 fn_80128EE4(void *);
extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern void *fn_80201814();
extern u32 fn_8003BD48(void *, void *);
extern void *fn_801A717C(void);
extern void fn_8012B344(void*);
extern void fn_801A7470(void *, int);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern unsigned long long fn_8020123C();
extern void fn_801A7228(void *);

#pragma opt_propagation off
u32 fn_80073728(void *object, void *argument)
{
    register void *saved_object = object;
    register void *resolved;
    register void *first;
    register void *second;
    register void *event;
    register u32 result;

    result = 0;
    resolved = argument;
    if ((fn_80128EE4(saved_object) & 0x20) != 0) {
        first = fn_801A7498(resolved);
        second = fn_801A7490(resolved);
        resolved = fn_80201814(first);
        fn_80201814(second);
        if (resolved != 0 && saved_object != 0) {
            result = fn_8003BD48(saved_object, argument);
            if ((result & 0x40) != 0) {
                event = fn_801A717C();
                fn_8012B344(saved_object);
                fn_801A7470(event, 0xB);
                fn_801A74A0(event, first);
                fn_801A74A8(event, first);
                fn_8020123C(0x35, first, first, event);
                fn_801A7228(event);
            }
        }
    }
    return result;
}

#pragma opt_propagation reset
