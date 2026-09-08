extern void* fn_80024570(void);
extern void fn_801E85A8(void*);

void* fn_801E8660(void)
{
    void* result = fn_80024570();
    if (result == 0) {
        return 0;
    }
    fn_801E85A8(result);
    return result;
}
