typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void EXIGetID(s32 chan, u32 dev, u64 *id);

void UnlockedHandler(s32 chan)
{
    u64 id;

    EXIGetID(chan, 0, &id);
}
