typedef unsigned short u16;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern u16 fn_8020C918(void);
extern s32 fn_80220D3C(s32 channel, u16 format, CardCallback callback);
extern void fn_8021C378(s32 channel, s32 result);
extern signed long fn_8021D558(signed long channel);

/* Format a memory card and wait for completion. */
s32 fn_802213DC(s32 channel)
{
    s32 result = fn_80220D3C(channel, fn_8020C918(), fn_8021C378);

    if (result < 0) {
        return result;
    }
    return fn_8021D558(channel);
}
