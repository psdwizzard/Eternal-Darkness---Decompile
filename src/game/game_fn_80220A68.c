typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern void __CARDSyncCallback(s32 channel, s32 result);
extern s32 CARDMountAsync(s32 channel, void *workArea,
                      CardCallback detachCallback, CardCallback attachCallback);
extern signed long __CARDSync(signed long channel);

/* Mount the card and wait for the asynchronous mount to finish. */
s32 CARDMount(s32 channel, void *workArea, CardCallback detachCallback)
{
    s32 result = CARDMountAsync(channel, workArea, detachCallback, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(channel);
}
