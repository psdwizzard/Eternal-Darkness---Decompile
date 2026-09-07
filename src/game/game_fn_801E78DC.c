typedef unsigned int u32;

extern void* fn_801FEA8C(u32 size, int kind, void* source, int line);
extern void* memset(void* destination, int value, u32 size);
extern unsigned char lbl_80264A98[];

void* fn_801E78DC(u32 size)
{
    u32* result;
    u32 rounded;

    rounded = (size + 31) >> 2;
    result = fn_801FEA8C(rounded + 4, 1, lbl_80264A98, 287);
    memset(result, 0, rounded + 4);
    result[0] = rounded * 4;
    return result;
}
