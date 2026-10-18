typedef signed int s32;
typedef unsigned int u32;

/* __CARDSync uses the SDK's signed-long s32 typedef in its definition. */
typedef signed long CARDSyncResult;
extern CARDSyncResult __CARDSync(CARDSyncResult chan);
extern void __CARDSyncCallback(s32 chan, s32 result);
extern s32 CARDCheckExAsync(s32 chan, u32 *xferBytes,
                     void (*callback)(s32, s32));

static inline s32 CARDCheckEx(s32 chan, u32 *xferBytes)
{
    s32 result = CARDCheckExAsync(chan, xferBytes, __CARDSyncCallback);

    if (result < 0 || xferBytes == 0)
        return result;
    return __CARDSync(chan);
}

/* CARDCheck */
s32 CARDCheck(s32 chan)
{
    u32 size;

    return CARDCheckEx(chan, &size);
}
