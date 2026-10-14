typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern void fn_8021C378(s32 channel, s32 result);
extern s32 fn_802208C8(s32 channel, void *workArea,
                      CardCallback detachCallback, CardCallback attachCallback);
extern signed long fn_8021D558(signed long channel);

/* Mount the card and wait for the asynchronous mount to finish. */
s32 fn_80220A68(s32 channel, void *workArea, CardCallback detachCallback)
{
    s32 result = fn_802208C8(channel, workArea, detachCallback, fn_8021C378);

    if (result < 0) {
        return result;
    }
    return fn_8021D558(channel);
}
