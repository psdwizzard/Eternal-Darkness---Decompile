typedef signed int s32;
typedef struct CARDStat CARDStat;
typedef void (*CARDCallback)(s32 chan, s32 result);

extern s32 fn_80222810(s32 chan, s32 fileNo, CARDStat *stat,
                     CARDCallback callback);
extern void fn_8021C378(s32 chan, s32 result);
extern signed long fn_8021D558(signed long chan);

/* CARDSetStatus: update a file's status and wait for completion. */
s32 fn_80222984(s32 chan, s32 fileNo, CARDStat *stat)
{
    s32 result = fn_80222810(chan, fileNo, stat, fn_8021C378);

    if (result < 0) {
        return result;
    }
    return fn_8021D558(chan);
}
