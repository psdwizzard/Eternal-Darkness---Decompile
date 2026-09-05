typedef unsigned char u8;

extern void* fn_801CDD00(u8 index, void** info);

void* fn_801CD200(u8 index)
{
    return fn_801CDD00(index, 0);
}
