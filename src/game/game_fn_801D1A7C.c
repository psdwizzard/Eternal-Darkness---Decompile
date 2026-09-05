extern void* fn_80201814(void);
extern void* fn_80201C24(void);
extern void* fn_80157924(void*);

int fn_801D1A7C(void)
{
    if (fn_80201814() != 0 && fn_80157924(fn_80201C24()) != 0) {
        return 1;
    }
    return 0;
}
