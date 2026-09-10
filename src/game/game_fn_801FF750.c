typedef unsigned int u32;

extern void fn_801FED48(void* data);
extern void* memcpy(void* destination, const void* source, u32 size);
extern void fn_801FEC84(void* data);
extern void DCFlushRange(void* address, u32 size);

void fn_801FF750(void** owner, u32 size, void* replacement)
{
    void* original = *owner;

    fn_801FED48(original);
    memcpy(replacement, original, size);
    fn_801FEC84(original);
    fn_801FEC84(replacement);
    DCFlushRange(replacement, size);
    *owner = replacement;
}
