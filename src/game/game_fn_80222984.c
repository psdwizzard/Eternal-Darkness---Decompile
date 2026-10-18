typedef signed int s32;
typedef struct CARDStat CARDStat;
typedef void (*CARDCallback)(s32 chan, s32 result);

extern s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat *stat,
                     CARDCallback callback);
extern void __CARDSyncCallback(s32 chan, s32 result);
extern signed long __CARDSync(signed long chan);

/* CARDSetStatus: update a file's status and wait for completion. */
s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat *stat)
{
    s32 result = CARDSetStatusAsync(chan, fileNo, stat, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(chan);
}
