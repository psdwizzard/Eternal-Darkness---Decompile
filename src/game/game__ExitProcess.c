extern void PPCHalt(void);

void _ExitProcess(void)
{
    PPCHalt();
}
