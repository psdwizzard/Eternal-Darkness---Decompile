typedef unsigned int u32;

extern void* fn_80201814(void);
extern void* fn_80201C24(void);
extern u32 fn_80157894(void*);

int fn_801D1AC0(void)
{
    int result = 0;

    if (fn_80201814() != 0) {
        void* current = fn_80201C24();
        if (current != 0) {
            u32 bit = (fn_80157894(current) >> 9) & 1;
            result = bit;
        }
    }
    return result;
}
