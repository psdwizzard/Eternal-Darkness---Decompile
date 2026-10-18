extern int __OSCurrHeap;
extern void OSFreeToHeap(int heap, void *ptr);

/* Release a cached resource from the resource heap. */
void TexFreeFunc(void *resource)
{
    OSFreeToHeap(__OSCurrHeap, resource);
}
