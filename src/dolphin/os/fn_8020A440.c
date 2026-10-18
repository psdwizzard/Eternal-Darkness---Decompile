typedef int (*DebuggerVector)(void);

int __OSDBJump(void)
{
    return ((DebuggerVector)0x60)();
}
