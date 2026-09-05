typedef unsigned int u32;

extern u32 lbl_8064D4EC;
extern u32 lbl_8064D4F8;
extern void* (*lbl_8064D4F4)(void*, u32);
extern void DCFlushRange(void*, u32);
extern void fn_801CD5D0(void*, u32, u32, u32, u32, u32);

u32 fn_801CDA24(void* data, u32 size)
{
    u32 chunk;
    u32 result;
    void* staging;

    size = (size + 31) & ~31;
    result = lbl_8064D4EC;
    if (lbl_8064D4F4 == 0) {
        DCFlushRange(data, size);
        fn_801CD5D0(data, lbl_8064D4EC, size, 0, 0, 0);
        lbl_8064D4EC += size;
        return result;
    }

    while (size != 0) {
        chunk = lbl_8064D4F8;
        if (size < chunk) {
            goto smaller;
        }
        goto selected;
smaller:
        chunk = size;
selected:
        staging = lbl_8064D4F4(data, chunk);
        DCFlushRange(staging, chunk);
        fn_801CD5D0(staging, lbl_8064D4EC, chunk, 0, 0, 0);
        lbl_8064D4EC += chunk;
        size -= chunk;
        data = (char*)data + chunk;
    }
    return result;
}
