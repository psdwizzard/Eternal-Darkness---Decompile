typedef unsigned int u32;
typedef unsigned char u8;

extern u32 aramWrite;
extern u32 aramUploadChunkSize;
extern void* (*aramUploadCallback)(u32, u32);
extern void DCFlushRange(void*, u32);
extern void aramUploadData(void*, u32, u32, u32, u32, u32);

u32 aramStoreData(void* src, u32 size)
{
    u32 chunk;
    u32 startPos;
    void* piece;
    u32 alignedSize;

    alignedSize = (size + 0x1f) & ~0x1f;
    startPos = aramWrite;

    if (aramUploadCallback == 0) {
        DCFlushRange(src, alignedSize);
        aramUploadData(src, aramWrite, alignedSize, 0, 0, 0);
        aramWrite += alignedSize;
        return startPos;
    }

    while (alignedSize != 0) {
        chunk = (alignedSize >= aramUploadChunkSize) ? aramUploadChunkSize : alignedSize;
        piece = aramUploadCallback((u32)src, chunk);
        DCFlushRange(piece, chunk);
        aramUploadData(piece, aramWrite, chunk, 0, 0, 0);
        alignedSize -= chunk;
        src = (u8*)src + chunk;
        aramWrite += chunk;
    }
    return startPos;
}
