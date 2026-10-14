typedef signed int s32;
typedef unsigned int u32;

/* __CARDSync uses the SDK's signed-long s32 typedef in its definition. */
typedef signed long CARDSyncResult;
extern CARDSyncResult fn_8021D558(CARDSyncResult chan);
extern void fn_8021C378(s32 chan, s32 result);
extern s32 fn_8021FB24(s32 chan, u32 *xferBytes,
                     void (*callback)(s32, s32));

static inline s32 CARDCheckEx(s32 chan, u32 *xferBytes)
{
    s32 result = fn_8021FB24(chan, xferBytes, fn_8021C378);

    if (result < 0 || xferBytes == 0)
        return result;
    return fn_8021D558(chan);
}

/* CARDCheck */
s32 fn_802200DC(s32 chan)
{
    u32 size;

    return CARDCheckEx(chan, &size);
}
