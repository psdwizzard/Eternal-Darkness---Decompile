typedef int BOOL;
typedef unsigned int u32;

extern BOOL fn_8020E88C(BOOL commit, u32 offset);

BOOL __OSUnlockSramEx(BOOL commit)
{
    return fn_8020E88C(commit, 0x14);
}
