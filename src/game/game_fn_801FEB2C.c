typedef unsigned int u32;

extern void* __OSCurrHeap;
extern void OSFreeToHeap(void*, u32);

void fn_801FEB2C(u32 size)
{
    OSFreeToHeap(__OSCurrHeap, size);
}
