typedef unsigned int u32;
typedef unsigned char u8;

extern u32 lbl_8064D4EC;
extern u32 lbl_8064D4F8;
extern void* (*lbl_8064D4F4)(u32, u32);
extern void DCFlushRange(void*, u32);
extern void fn_801CD5D0(void*, u32, u32, u32, u32, u32);

u32 fn_801CDA24(void* src, u32 size)
{
    u32 chunk;
    u32 startPos;
    void* piece;
    u32 alignedSize;

    alignedSize = (size + 0x1f) & ~0x1f;
    startPos = lbl_8064D4EC;

    if (lbl_8064D4F4 == 0) {
        DCFlushRange(src, alignedSize);
        fn_801CD5D0(src, lbl_8064D4EC, alignedSize, 0, 0, 0);
        lbl_8064D4EC += alignedSize;
        return startPos;
    }

    while (alignedSize != 0) {
        chunk = (alignedSize >= lbl_8064D4F8) ? lbl_8064D4F8 : alignedSize;
        piece = lbl_8064D4F4((u32)src, chunk);
        DCFlushRange(piece, chunk);
        fn_801CD5D0(piece, lbl_8064D4EC, chunk, 0, 0, 0);
        alignedSize -= chunk;
        src = (u8*)src + chunk;
        lbl_8064D4EC += chunk;
    }
    return startPos;
}
