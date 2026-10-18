typedef unsigned int u32;

extern void GXFlush(void);
extern void GXResetWriteGatherPipe(void);

u32 fn_801EB30C(void)
{
    GXFlush();
    GXResetWriteGatherPipe();
    return (*(volatile u32*)0xCC003014 & ~0x04000000) + 0x80000000;
}
