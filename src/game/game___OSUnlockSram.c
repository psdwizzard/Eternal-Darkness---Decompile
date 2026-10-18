typedef int BOOL;
typedef unsigned int u32;

extern BOOL UnlockSram(BOOL commit, u32 offset);

BOOL __OSUnlockSram(BOOL commit)
{
    return UnlockSram(commit, 0);
}
