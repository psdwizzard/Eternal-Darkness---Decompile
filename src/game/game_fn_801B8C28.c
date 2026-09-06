typedef unsigned int u32;

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern unsigned char* fn_801B3A2C(u32, u32);

void fn_801B8C28(u32 handle, u32 value)
{
    fn_801CE2B8();
    fn_801B3A2C(handle, value);
    fn_801CE280();
}
